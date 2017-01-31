/**************************************************************************
This file is part of JahshakaVR, VR Authoring Toolkit
http://www.jahshaka.com
Copyright (c) 2016  GPLv3 Jahshaka LLC <coders@jahshaka.com>

This is free software: you may copy, redistribute
and/or modify it under the terms of the GPLv3 License

For more information see the LICENSE file
*************************************************************************/

#ifndef ACCORDIANBLADEWIDGET_H
#define ACCORDIANBLADEWIDGET_H

#include <QWidget>

namespace Ui {
class AccordianBladeWidget;
}

class TransformEditor;
class ColorValueWidget;
class TexturePicker;
class HFloatSlider;
class CheckBoxProperty;

class AccordianBladeWidget : public QWidget
{
    Q_OBJECT

public:

    int minimum_height;

    explicit AccordianBladeWidget(QWidget *parent = 0);
    ~AccordianBladeWidget();

    TransformEditor* addTransform();
    void addCheckBoxOption( QString name);
    void setMaxHeight( int height );
    ColorValueWidget* addColorPicker( QString name );
    TexturePicker* addTexturePicker( QString name );
    void addFilePicker( QString name, QString fileextention );
    void setContentTitle( QString title );
    HFloatSlider* addFloatValueSlider( QString name, float range_1 , float range_2 );
    CheckBoxProperty* addCheckBox( QString name, bool value = false );

    void expand();

private slots:
    void on_toggle_clicked();

private:
    Ui::AccordianBladeWidget *ui;
};

#endif // ACCORDIANBLADEWIDGET_H