#ifndef ITEMINTERFACE_H
#define ITEMINTERFACE_H

#include <QString>
#include <QVariant>

class ItemInterface
{
public:
    static const int MAX_NAME_LENGTH = 32;

    enum class RenameResult {
        Ok,
        Empty,
        TooLong,
        Duplicate,
        NotValid
    };

    virtual QString name() const = 0;
    virtual RenameResult rename(const QString& name) = 0;
    virtual QVariant display() const = 0;
    virtual QVariant decoration() const = 0;
};

#endif // ITEMINTERFACE_H
