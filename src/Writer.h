//
// Created by wang on 2019/12/7.
//

#ifndef BUILD__WRITER_H_
#define BUILD__WRITER_H_

#include <dds/DdsDcpsPublicationC.h>
#include <ace/Task.h>


class Writer : public ACE_Task_Base
{
 public:
  Writer (::DDS::DataWriter_ptr writer_ptr);
  void start();
  void end();

  /* Lanch a thread to write. */
  virtual int svc();
  bool is_finished() const;
  int get_timeout_writes() const;

 private:
  ::DDS::DataWriter_var writer_var_;
  ACE_Atomic_Op<ACE_SYNCH_MUTEX, int> finished_instances_;
  ACE_Atomic_Op<ACE_SYNCH_MUTEX, int> timeout_writes_;
};

#endif //BUILD__WRITER_H_
