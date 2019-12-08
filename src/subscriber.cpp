#include "DataReaderListener.h"
#include "MessengerTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/SubscriberImpl.h>
#include <dds/DCPS/transport/tcp/TcpInst.h>
#include <dds/DCPS/StaticIncludes.h>

#include <ace/streams.h>
#include <ace/Get_Opt.h>
#include <ace/OS_NS_unistd.h>

int ACE_TMAIN (int argc, char** argv) {
  try {
    DDS::DomainParticipantFactory_var dpf;
    DDS::DomainParticipant_var participant;

    dpf = TheParticipantFactoryWithArgs(argc, argv);
    participant = dpf->create_participant(111,
                                          PARTICIPANT_QOS_DEFAULT,
                                          DDS::DomainParticipantListener::_nil(),
                                          OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(participant.in())) {
      std::cerr << "create_participant failed." << std::endl;
      return 1;
    }

    Messenger::MessageTypeSupportImpl* mts_servant = new Messenger::MessageTypeSupportImpl();
    OpenDDS::DCPS::LocalObject_var safe_servant = mts_servant;

    if (DDS::RETCODE_OK != mts_servant->register_type(participant.in(), "")) {
      std::cerr << "Failed to register the MessageTypeSupport." << std::endl;
      exit(1);
    }

    CORBA::String_var type_name = mts_servant->get_type_name();

    DDS::TopicQos topic_qos;
    participant->get_default_topic_qos(topic_qos);
    DDS::Topic_var topic = participant->create_topic("Movie Discussion List",
                                                     type_name.in(),
                                                     topic_qos,
                                                     DDS::TopicListener::_nil(),
                                                     ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(topic.in())) {
      std::cerr << "Failed to create_topic." << std::endl;
      exit(1);
    }

    // Create the subscriber
    DDS::Subscriber_var sub =
        participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,
                                       DDS::SubscriberListener::_nil(),
                                       ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(sub.in())) {
      std::cerr << "Failed to create_subscriber." << std::endl;
      exit(1);
    }

    // activate the listener
    DDS::DataReaderListener_var listener(new DataReaderListenerImpl);
    DataReaderListenerImpl* listener_servant =
        dynamic_cast<DataReaderListenerImpl*>(listener.in());

    if (CORBA::is_nil(listener.in())) {
      std::cerr << "listener is nil." << std::endl;
      exit(1);
    }

    if (!listener_servant) {
      ACE_ERROR_RETURN((LM_ERROR,
          ACE_TEXT("%N:%l main()")
          ACE_TEXT(" ERROR: listener_servant is nil (dynamic_cast failed)!\n")), -1);
    }

    // Create the Datareaders
    DDS::DataReaderQos dr_qos;
    sub->get_default_datareader_qos(dr_qos);
    DDS::DataReader_var dr = sub->create_datareader(topic.in(),
                                                    dr_qos,
                                                    listener.in(),
                                                    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (CORBA::is_nil(dr.in())) {
      std::cerr << "create_datareader failed." << std::endl;
      exit(1);
    }

    int expected = 10;
    while (listener_servant->num_reads() < expected) {
      ACE_OS::sleep(1);
    }

    if (!CORBA::is_nil(dr.in())) {
      std::cerr << "create_datareader failed." << std::endl;
      exit(1);
    }

    if (!CORBA::is_nil(dpf.in())) {
      dpf->delete_participant(participant.in());
    }
    ACE_OS::sleep(2);

    TheServiceParticipant->shutdown();

  } catch (CORBA::Exception& e) {
    std::cerr << "SUB: Exception caught in main(): " << std::endl << e << std::endl;
    return 1;
  }

  return 0;
}