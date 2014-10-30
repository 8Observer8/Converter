#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>

struct Character
{
    Character( QString x, QString y, QString z ) :
        m_x( x ), m_y( y ), m_z( z )
    {

    }

    QString x() const {
        return m_x;
    }

    QString y() const {
        return m_y;
    }

    QString z() const {
        return m_z;
    }

    QString m_x;
    QString m_y;
    QString m_z;
};

#endif // CHARACTER_H
