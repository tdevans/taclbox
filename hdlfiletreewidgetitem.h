#ifndef HDLFILETREEWIDGETITEM_H
#define HDLFILETREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "hdlfile.h"

class HdlFileTreeWidgetItem : public QTreeWidgetItem
{
public:
    HdlFileTreeWidgetItem(const HdlFile& file);

    const HdlFile& hdlFile() const;

private:
    const HdlFile& mFile;
};

#endif // HDLFILETREEWIDGETITEM_H
