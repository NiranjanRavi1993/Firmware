#pragma once
#include <uavcan/uavcan.hpp>
#include <uavcan/equipment/teste/TesteReceive.hpp>
#include <perf/perf_counter.h>
#include <uORB/topics/teste_receive.h>

class UavcanTeste
{
public:
    UavcanTeste(uavcan::INode &node);
    ~UavcanTeste();

    int init();

/**
* TesteReceive message reception will be reported via this callback.
*/
private:
    void teste_receive_sub_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::teste::TesteReceive> &msg);

    typedef uavcan::MethodBinder<UavcanTeste *,void (UavcanTeste::*)(const
    uavcan::ReceivedDataStructure<uavcan::equipment::teste::TesteReceive>&)>
    StatusCbBinder;
/*
* libuavcan related things
*/
    uavcan::MonotonicTime   _prev_cmd_pub;

    uavcan::INode   &_node;

    uavcan::Subscriber<uavcan::equipment::teste::TesteReceive, StatusCbBinder>
    _uavcan_sub_status;

    teste_receive_s _teste_receive = {};
    orb_advert_t    _teste_receive_pub = nullptr;
};
