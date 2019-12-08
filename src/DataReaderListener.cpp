#include "DataReaderListener.h"
#include "MessengerTypeSupportC.h"
#include "MessengerTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>

DataReaderListenerImpl::DataReaderListenerImpl()
    : num_reads_(0)
{}

DataReaderListenerImpl::~DataReaderListenerImpl()
{}

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader) {
  ++num_reads_;

  try {
    Messenger::MessageDataReader_var message_dr = Messenger::MessageDataReader::_narrow(reader);
    if (CORBA::is_nil(message_dr.in())) {
      std::cerr << "read: _narrow failed." << std::endl;
      exit(1);
    }

    Messenger::Message message;
    DDS::SampleInfo si;
    DDS::ReturnCode_t status = message_dr->take_next_sample(message, si);

    if (status == DDS::RETCODE_OK) {
      std::cout << "Message: subject    = " << message.subject.in() << std::endl
                << "         subject_id = " << message.subject_id   << std::endl
                << "         from       = " << message.from.in()    << std::endl
                << "         count      = " << message.count        << std::endl
                << "         text       = " << message.text.in()    << std::endl;
      std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
    } else if (status == DDS::RETCODE_NO_DATA) {
      std::cerr << "ERROR: reader received DDS::RETCODE_NO_DATA!" << std::endl;
    } else {
      std::cerr << "ERROR: read Message: Error: " << status << std::endl;
    }
  } catch (CORBA::Exception& e) {
    std::cerr << "Exception caught in read:" << std::endl << e << std::endl;
    exit(1);
  }
}

void DataReaderListenerImpl::on_requested_deadline_missed(
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_requested_deadline_missed" << std::endl;
}

void DataReaderListenerImpl::on_requested_incompatible_qos(
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_requested_incompatible_qos" << std::endl;
}

void DataReaderListenerImpl::on_liveliness_changed(
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_liveliness_changed" << std::endl;
}

void DataReaderListenerImpl::on_subscription_matched(
    ::DDS::DataReader_ptr reader,
    const ::DDS::SubscriptionMatchedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_subscription_matched" << std::endl;
}

void DataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_sample_rejected" << std::endl;
}

void DataReaderListenerImpl::on_sample_lost(
    DDS::DataReader_ptr reader,
    const DDS::SampleLostStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_subscription_disconnected" << std::endl;
}


void DataReaderListenerImpl::on_subscription_disconnected(
    DDS::DataReader_ptr reader,
    const ::OpenDDS::DCPS::SubscriptionDisconnectedStatus &status){
  std::cerr << "DataReaderListenerImpl::on_subscription_disconnected" << std::endl;
}

void DataReaderListenerImpl::on_subscription_reconnected(
    DDS::DataReader_ptr reader,
    const ::OpenDDS::DCPS::SubscriptionDisconnectedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_subscription_reconnected" << std::endl;
}

void DataReaderListenerImpl::on_subscription_lost(
    DDS::DataReader_ptr reader,
    const ::OpenDDS::DCPS::SubscriptionDisconnectedStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_subscription_lost" << std::endl;
}

void DataReaderListenerImpl::on_budget_exceeded(
    DDS::DataReader_ptr reader,
    const ::OpenDDS::DCPS::BudgetExceededStatus &status) {
  std::cerr << "DataReaderListenerImpl::on_budget_exceeded" << std::endl;
}