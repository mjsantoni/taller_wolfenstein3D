#ifndef TP_WOLFENSTEIN_EVENT_H
#define TP_WOLFENSTEIN_EVENT_H


class Event {
private:
    int player_id;
    int event_id;
    double angle;
public:
    Event(int _player_id, int _event_id, double _angle);

};


#endif //TP_WOLFENSTEIN_EVENT_H
