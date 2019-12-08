#include "MessengerTypeSupportImpl.h"
#include "Writer.h"
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/PublisherImpl.h>
#include <dds/DCPS/transport/tcp/TcpInst.h>

#include "dds/DCPS/StaticIncludes.h"

#include <ace/streams.h>
#include <ace/Get_Opt.h>
#include <ace/OS_NS_unistd.h>

int ACE_TMAIN(int argc, char** argv) {
  try {
    DDS::DomainParticipantFactory_var dpf =
        TheParticipantFactoryWithArgs(argc, argv);
    DDS::DomainParticipant_var participant =
        dpf->create_participant(111,
                                PARTICIPANT_QOS_DEFAULT,
                                DDS::DomainParticipantListener::_nil(),
                                ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(participant.in())) {
      std::cerr << "Create_participant failed. " << std::endl;
      return 1;
    }

    Messenger::MessageTypeSupportImpl* servant = new Messenger::MessageTypeSupportImpl();
    OpenDDS::DCPS::LocalObject_var safe_servant = servant;

    if (DDS::RETCODE_OK != servant->register_type(participant.in(), "")) {
      std::cerr << "register_type failed." << std::endl;
      exit(1);
    }

    CORBA::String_var type_name = servant->get_type_name();

    DDS::TopicQos topic_qos;
    participant->get_default_topic_qos(topic_qos);
    DDS::Topic_var topic =
        participant->create_topic("Movie Discussion List",
                                  type_name.in(),
                                  topic_qos,
                                  DDS::TopicListener::_nil(),
                                  ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(topic.in())) {
      std::cerr << "create_topic failed." << std::endl;
      exit(1);
    }

    DDS::Publisher_var pub =
        participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                      DDS::PublisherListener::_nil(),
                                      ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(pub.in())) {
      std::cerr << "create_publisher failed." << std::endl;
      exit(1);
    }

    // create the dataWriter
    DDS::DataWriterQos dw_qos;
    pub->get_default_datawriter_qos(dw_qos);
    DDS::DataWriter_var dw =
        pub->create_datawriter(topic.in(),
                               dw_qos,
                               DDS::DataWriterListener::_nil(),
                               ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(dw.in())) {
      std::cerr << "create_datawriter failed." << std::endl;
      exit(1);
    }

    Writer* writer = new Writer(dw.in());
    writer->start();
    while (!writer->is_finished()) {
      ACE_Time_Value small_time(0, 250000);
      ACE_OS::sleep(small_time);
    }

    // cleanup
    writer->end();
    delete writer;
    participant->delete_contained_entities();
    dpf->delete_participant(participant.in());
    TheServiceParticipant->shutdown();

  } catch (CORBA::Exception& e) {
    std::cerr << "PUB: Exception caught in main.cpp:" << std::endl << e << std::endl;
  }

  return 0;

}