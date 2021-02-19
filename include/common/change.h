#ifndef TP_WOLFENSTEIN_CHANGE_H
#define TP_WOLFENSTEIN_CHANGE_H

#include "common/changes.h"
#include <sstream>

class Change {
public:
    int change_id;
    int id;
    int value1;
    int value2;
    bool is_global;

    /* Server-side constructor */
    Change(int _change_id, int _id, int _value1, int _value2, bool _is_global);

    /* Client-side constructor */
    Change(int _change_id, int _id, int _value1, int _value2);

    /* Invalid default constructor */
    Change();

    bool isInvalid() const;

    int getChangeID() const;
    int getPlayerID() const;
    int getFirstValue() const;
    int getSecondValue() const;
    bool isGlobal() const;

    /* Serializa sus valores a bytes para enviar */
    std::string serialize();
};

#endif //TP_WOLFENSTEIN_CHANGE_H
