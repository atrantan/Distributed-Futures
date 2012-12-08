#ifndef _RR_H
#define _RR_H

#include "scheduler.hpp"
#include "../communication/communication.hpp"
#include <map>

namespace futures {
namespace scheduler {

class RRScheduler : public Scheduler {
private:
    unsigned int master_id;
    unsigned int total_workers;
    unsigned int curr_worker_id;
    communication::CommInterface* comm;
    Process *proc;
public:
    RRScheduler(communication::CommInterface* commInterface);
    ~RRScheduler();
    static Scheduler* create(communication::CommInterface *commInterface);
    int nextAvaibleWorkerId();
    void set_status(ProcStatus status);
    bool terminate();
};

}
}

#endif