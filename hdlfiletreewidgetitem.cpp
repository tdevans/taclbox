#include "hdlfiletreewidgetitem.h"

HdlFileTreeWidgetItem::HdlFileTreeWidgetItem(const HdlFile &file)
    :mFile(file)
{
    setText(0, file.fileName());
}

const HdlFile &HdlFileTreeWidgetItem::hdlFile() const
{
    return mFile;
}
