#-------------------------------------------------
#
# Project created by QtCreator 2013-02-14T18:38:26
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tsunami-opt
TEMPLATE = app
DEFINES += _DEBUG_=1

SOURCES += main.cpp\
        deviceworkspace.cpp \
    gui/formminimisation.cpp \
    gui/formparameters.cpp \
    gui/formgraphics.cpp \
    gui/formmeasures.cpp \
    gui/formmodels.cpp \
    gui/delegates/delegatecheckbox.cpp \
    gui/delegates/delegatereadonly.cpp \
    gui/formstrategy.cpp \
    gui/editormeasures.cpp \
    gui/delegates/delegatecombobox.cpp \
    gui/delegates/info_block/delegateinfocheckbox.cpp \
    gui/delegates/info_block/delegateinfodate.cpp \
    core/tdevice.cpp \
    core/tparameter.cpp \
    core/tterminal.cpp \
    devices/bjt.cpp \
    core/extractor.cpp \
    core/tstrategy.cpp \
    core/tdblayer.cpp \
    managers/managerdevices.cpp \
    managers/managerworkspace.cpp \
    gui/dialogs/dialogopendevice.cpp \
    core/tmeasure.cpp \
    core/tdataset.cpp \
    minimisations/minhookejeeves.cpp \
    core/tparameterset.cpp \
    gui/dialogs/dialognewdevice.cpp \
    managers/managerstrategy.cpp \
    gui/dialogs/dialognewparameterset.cpp \
    managers/managerparameterset.cpp \
    managers/managermeasures.cpp \
    qcustomplot.cpp \
    gui/dialogs/dialogaddmeasure.cpp \
    managers/managerextractor.cpp \
    gui/dialogs/viewers/viewerplot.cpp \
    devices/jfet.cpp \
    devices/mosfet.cpp \
    core/tmodel.cpp \
    gui/dialogs/dialogaddconstant.cpp \
    gui/dialogs/dialogsaveparameters.cpp \
    minimisations/minquasinewton.cpp \
    minimisations/cmatrix.cpp \
    core/treport.cpp \
    reports/reportoptimisation.cpp \
    gui/formsetting.cpp \
    gui/formweightconst.cpp \
    core/tsetting.cpp \
    gui/dialogs/dialogdeletedevices.cpp

HEADERS  += deviceworkspace.h \
    gui/formminimisation.h \
    gui/formparameters.h \
    gui/formgraphics.h \
    gui/formmeasures.h \
    gui/formmodels.h \
    gui/delegates/delegatecheckbox.h \
    gui/delegates/delegatereadonly.h \
    gui/formstrategy.h \
    gui/editormeasures.h \
    gui/delegates/delegatecombobox.h \
    gui/delegates/info_block/delegateinfocheckbox.h \
    gui/delegates/info_block/delegateinfodate.h \
    gui/delegates/delegates.h \
    core/tparameter.h \
    core/tterminal.h \
    devices/bjt.h \
    gui/gui.h \
    core/extractor.h \
    core/tstrategy.h \
    core/tdblayer.h \
    managers/managerdevices.h \
    managers/managerworkspace.h \
    gui/dialogs/dialogopendevice.h \
    gui/dialogs/dialogs.h \
    core/tmeasure.h \
    core/tdataset.h \
    defines.h \
    minimisations/minhookejeeves.h \
    minimisations/minimisations.h \
    core/tparameterset.h \
    gui/dialogs/dialognewdevice.h \
    managers/managerstrategy.h \
    gui/dialogs/dialognewparameterset.h \
    managers/managerparameterset.h \
    managers/managermeasures.h \
    qcustomplot.h \
    gui/dialogs/dialogaddmeasure.h \
    managers/managerextractor.h \
    gui/dialogs/viewers/viewerplot.h \
    devices/jfet.h \
    devices/devices.h \
    devices/mosfet.h \
    core/tmodel.h \
    gui/dialogs/dialogaddconstant.h \
    gui/dialogs/dialogsaveparameters.h \
    minimisations/minquasinewton.h \
    minimisations/cmatrix.h \
    core/treport.h \
    reports/reportoptimisation.h \
    gui/formsetting.h \
    gui/formweightconst.h \
    core/tsetting.h \
    gui/dialogs/dialogdeletedevices.h

FORMS    += deviceworkspace.ui \
    gui/formminimisation.ui \
    gui/formparameters.ui \
    gui/formmeasures.ui \
    gui/formmodels.ui \
    gui/formgraphics.ui \
    gui/formstrategy.ui \
    gui/editormeasures.ui \
    gui/dialogs/dialogopendevice.ui \
    gui/dialogs/dialognewdevice.ui \
    gui/dialogs/dialognewparameterset.ui \
    gui/dialogs/dialogaddmeasure.ui \
    gui/dialogs/viewers/viewerplot.ui \
    gui/dialogs/dialogaddconstant.ui \
    gui/dialogs/dialogsaveparameters.ui \
    gui/formsetting.ui \
    gui/formweightconst.ui \
    gui/dialogs/dialogdeletedevices.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    dbase_plan.txt \
    measures_ser.txt
