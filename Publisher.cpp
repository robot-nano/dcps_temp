//
// Created by wang on 2019/11/27.
//

#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.cpp>
#include <iostream>

int main(int argc, char** argv) {
  try {
    DDS::DomainParticipantFactory_var dpf =
        TheParticipantFactoryWithArgs(argc, argv);
    DDS::DomainParticipant_var participant_var =
        dpf->create_participant(42, PARTICIPANT_QOS_DEFAULT,
                                0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (!participant_var) {
      std::cerr << "create_participant failed." << std::endl;
      return 1;
    }
  }

}