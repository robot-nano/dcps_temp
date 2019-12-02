// -*- C++ -*-
// ============================================================================
/**
 *  @file   publisher.cpp
 *
 *
 *
 */
// ============================================================================

#include "MessengerTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/PublisherImpl.h>
#include <dds/DCPS/transport/tcp/TcpInst.h>

#include "dds/DCPS/StaticIncludes.h"

#include <ace/streams.h>
#include "ace/Get_Opt.h"
#include "ace/OS_NS_unistd.h"

int main(int argc, char** argv) {
  try {
    DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);
    DDS::DomainParticipant_var participant = dpf->create_participant(42,
                                                                     PARTICIPANT_QOS_DEFAULT,
                                                                     0,
                                                                     OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!participant) {
      std::cerr << "create_participant failed." << std::endl;
      return 1;
    }

    Messenger::MessageTypeSupport_var mts =
        new Messenger::MessageTypeSupportImpl();
    if (DDS::RETCODE_OK != mts->register_type(participant, "")) {
      std::cerr << "register_type failed." << std::endl;
      return 1;
    }
    CORBA::String_var type_name = mts->get_type_name();
    DDS::Topic_var topic =
        participant->create_topic("Movie Discussion List",
                                  type_name,
                                  TOPIC_QOS_DEFAULT,
                                  0,
                                  OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!topic) {
      std::cerr << "create_topic failed." << std::endl;
      return 1;
    }

    DDS::Publisher_var pub =
        participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                      0,
                                      OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!pub) {
      std::cerr << "create_publisher failed." << std::endl;
      return 1;
    }

    DDS::DataWriter_var writer =
        pub->create_datawriter(topic,
                               DATAWRITER_QOS_DEFAULT,
                               0,
                               OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!writer) {
      std::cerr << "create_datawriter failed." << std::endl;
      return 1;
    }

    Messenger::MessageDataWriter_var message_writer =
        Messenger::MessageDataWriter::_narrow(writer);

    DDS::StatusCondition_var condition =
        writer->get_statuscondition();
    condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

    while(true) {
      DDS::PublicationMatchedStatus matches;
      if (writer->get_publication_matched_status(matches) != DDS::RETCODE_OK) {
        std::cerr << "get_publication_matched_status failed!" << std::endl;
        return 1;
      }

      if (matches.current_count >= 1) {
        break;
      }

      DDS::ConditionSeq conditions;
      DDS::Duration_t timeout = {60, 0};
    }

  } catch (double) {

  }

}