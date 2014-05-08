#include "skype1ico.h"

setIconProto realSetIcon;
QHash<qint32, QIcon> replace;
QString theme_dir, unknown_dir;

void initMyself() {
    realSetIcon = &QSystemTrayIcon::setIcon;
    void *ptr;
    memcpy(&ptr, &realSetIcon, sizeof(ptr));
    Dl_info nfo;
    dladdr(ptr, &nfo);
    ptr=dlsym(RTLD_NEXT, nfo.dli_sname);
    memcpy(&realSetIcon, &ptr, sizeof(ptr));
}

QString emptyDefault (QString query, QString def) {
    if (query.isEmpty()) {
        return def;
    }
    return query;
}

QString findThemeDir() {

    QStringList themes, list;

    themes << emptyDefault(qgetenv("SKYPE1ICO_THEME"), QIcon::themeName())
           << DEFAULT_THEME;

    list << qgetenv("HOME") + "/.local/share/skype1ico/"
         << THEMES_DIR;

    foreach (QString data_dir, QString(qgetenv("XDG_DATA_DIRS")).split(":")) {
        list << data_dir + "/skype1ico/";
    }

    foreach(QString theme, themes) {
        foreach (QString ico_root, list) {
            QString path = QString("%1/%2/").arg(ico_root, theme);
            if (QFile::exists( path + "themerc" )) {
                return path;
            }
        }
    }

    return "";
}

void readConfig(QString theme_dir) {
    QFile input_file(theme_dir + "themerc");
    if (input_file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&input_file);

        QIcon value;

        while ( !in.atEnd() ) {
            QString line = in.readLine();

            if (line.endsWith(':')) {
                line.chop(1);
                value = QIcon(theme_dir + line);
            }
            else if (line.endsWith('!')) {
                line.chop(1);
                value = QIcon::fromTheme(line);
            }
            else if (!line.startsWith('#') && !value.isNull()) {
                qint32 key = line.trimmed().toInt();
                replace.insert(key, value);
            }

        }
        input_file.close();
    }
}

extern void QSystemTrayIcon::setIcon(const QIcon &icon) {
    if (realSetIcon == NULL) {
        initMyself();
        theme_dir = findThemeDir();
        readConfig(theme_dir);
    }

    QPixmap pixmap = icon.pixmap(QSize(24, 24));
    qint32 key = Hashing::hashPixmap(pixmap);

    if (!replace.contains(key)) {
        pixmap.save(QString(qgetenv("HOME")) + "/.skype1ico/" + QString::number(key) + ".png");
    }

    (this->*realSetIcon) (replace.value(key, icon));

}

