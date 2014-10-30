#include "Dialog.h"
#include "ui_Dialog.h"
#include "Character.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_fileName = QString( "C:/Output.xml" );
    ui->outputLineEdit->setText( m_fileName );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_selectInputFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"),
                                QString(),
                                tr("Text Files (*.txt)") );

    if ( fileName.isEmpty() ) {
        return;
    }

    QFile file( fileName );

    if ( !file.open( QIODevice::ReadOnly ) ) {
        QMessageBox::critical(
                    this,
                    tr( "Ошибка" ),
                    tr( "Не могу открыть файл: \"%1\"" ).arg( fileName ) );
        return;
    }

    ui->inputLineEdit->setText( fileName );

    QRegExp rx("(\\d+,\\d+\\|\\d+,\\d+\\|\\d+,\\d+)");
    QString str;
    str = file.readAll();
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {
        QString s = rx.cap(1);
        QStringList list = s.split( "|" );
        if ( list.size() == 3 ) {
            m_characters.push_back( Character( list[0], list[1], list[2] ) );
        }
        pos += rx.matchedLength();
    }

    QDomDocument doc( "Characters" );
    QDomElement mainElement = doc.createElement( "Hotspots" );
    doc.appendChild( mainElement );

    for ( size_t i = 0; i < m_characters.size(); ++i ) {
        QDomElement hotspot = doc.createElement( "Hotspot" );
        mainElement.appendChild( hotspot );

        QDomAttr xAttr = doc.createAttribute( "X" );
        xAttr.setValue( m_characters[i].x() );
        hotspot.setAttributeNode( xAttr );

        QDomAttr yAttr = doc.createAttribute( "Y" );
        yAttr.setValue( m_characters[i].y() );
        hotspot.setAttributeNode( yAttr );

        QDomAttr zAttr = doc.createAttribute( "Z" );
        zAttr.setValue( m_characters[i].z() );
        hotspot.setAttributeNode( zAttr );
    }

    QFile outputfile( m_fileName );
    if ( !outputfile.open( QIODevice::WriteOnly ) ) {
        QMessageBox::critical(
                    this,
                    tr( "Ошибка" ),
                    tr( "Не могу открыть файл: \"%1\"" ).arg( fileName ) );
        return;
    }

    QTextStream( &outputfile ) << doc.toString();
}
