/***************************************************************************
 *   Copyright (c) 2021 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef GUI_UILOADER_H
#define GUI_UILOADER_H

#include <QUiLoader>
#include <CXX/Extensions.hxx>


namespace Gui {

class PySideUicModule : public Py::ExtensionModule<PySideUicModule>
{

public:
    PySideUicModule();
    virtual ~PySideUicModule() {}

private:
    Py::Object loadUiType(const Py::Tuple& args);
    Py::Object loadUi(const Py::Tuple& args);
};

/**
 * The UiLoader class provides the abitlity to use the widget factory
 * framework of FreeCAD within the framework provided by Qt. This class
 * extends QUiLoader by the creation of FreeCAD specific widgets.
 * @author Werner Mayer
 */
class UiLoader : public QUiLoader
{
public:
    UiLoader(QObject* parent=0);
    virtual ~UiLoader();

    /**
     * Creates a widget of the type \a className with the parent \a parent.
     * For more details see the documentation to QWidgetFactory.
     */
    QWidget* createWidget(const QString & className, QWidget * parent=0,
                          const QString& name = QString());
private:
    QStringList cw;
};

// --------------------------------------------------------------------

class UiLoaderPy : public Py::PythonExtension<UiLoaderPy>
{
public:
    static void init_type(void);    // announce properties and methods

    UiLoaderPy();
    ~UiLoaderPy();

    Py::Object repr();
    Py::Object createWidget(const Py::Tuple&);
    Py::Object load(const Py::Tuple&);

private:
    static PyObject *PyMake(struct _typeobject *, PyObject *, PyObject *);

private:
    UiLoader loader;
};

} // namespace Gui

#endif // GUI_UILOADER_H