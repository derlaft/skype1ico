#include "skype1ico.h"

setIconProto realSetIcon;
QHash<qint32, QIcon> replace;

void initMyself() {
    realSetIcon = &QSystemTrayIcon::setIcon;
    void *ptr;
    memcpy(&ptr, &realSetIcon, sizeof(ptr));
    Dl_info nfo;
    dladdr(ptr, &nfo);
    ptr=dlsym(RTLD_NEXT, nfo.dli_sname);
    memcpy(&realSetIcon, &ptr, sizeof(ptr));
}

void readConfig() {
    QFile input_file("config");
    if (input_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input_file);

        QIcon value;

        while ( !in.atEnd() )
        {
            QString line = in.readLine();

            if (line.endsWith(':')) {
                line.chop(1);
                value = QIcon(QString("replace/%1").arg( line ));

            }
            else if (!line.startsWith('#') && !value.isNull()) {

                qint32 key = line.trimmed().toInt();
                replace.insert(key, value);

                //printf("lol %d\n", key);
            }

        }
        input_file.close();
    }
}

extern void QSystemTrayIcon::setIcon(const QIcon &icon) {
    if (realSetIcon == NULL) {
        initMyself();
        readConfig();
    }

    QPixmap pixmap = icon.pixmap(QSize(24, 24));
    qint32 key = Hashing::hashPixmap(pixmap);

    if (!replace.contains(key)) {
        pixmap.save(QString("source/%1.png").arg( key ));
    }

    (this->*realSetIcon) (replace.value(key, icon));

}

