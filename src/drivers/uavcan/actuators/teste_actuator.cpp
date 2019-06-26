#include "teste_actuator.hpp"
#include <systemlib/err.h>

UavcanTeste::UavcanTeste(uavcan::INode &node) :
    _node(node),
    _uavcan_sub_status(node)
{
}
UavcanTeste::~UavcanTeste()
{
}
int UavcanTeste::init()
{
     printf("This line is getting executed\n");
    int res = _uavcan_sub_status.start(StatusCbBinder(this, &UavcanTeste::teste_receive_sub_cb));

    if (res < 0) {
        warnx("uavcan sub failed %i", res);
        printf("UAVCAN failed here");
        return res;
        }

        return 0;
}

void UavcanTeste::teste_receive_sub_cb(const uavcan::ReceivedDataStructure<uavcan::equipment::teste::TesteReceive> &msg)
{
     _teste_receive.inc=msg.recebe;


     uint8_t node= msg.getSrcNodeID().get();
     printf("%d", node);


    if (_teste_receive_pub != nullptr)
    {
    (void)orb_publish(ORB_ID(teste_receive), _teste_receive_pub,
    &_teste_receive);
    }

    else

    {
    _teste_receive_pub = orb_advertise(ORB_ID(teste_receive),
    &_teste_receive);
    }
}
