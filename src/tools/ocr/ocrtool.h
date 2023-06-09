// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Yurii Puchkov & Contributors
//

#ifndef FLAMESHOT_OCRTOOL_H
#define FLAMESHOT_OCRTOOL_H

#include <QObject>
#include "src/tools/abstractactiontool.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class QPixmap;
class QWidget;

class OCRTool : public AbstractActionTool
{
    Q_OBJECT
public:
    explicit OCRTool(QObject* parent = nullptr);

    bool closeOnButtonPressed() const override;

    QIcon icon(const QColor& background, bool inEditor) const override;
    QString name() const override;
    QString description() const override;

    CaptureTool* copy(QObject* parent = nullptr) override;

protected:
    CaptureTool::Type type() const override;

public slots:
    void pressed(CaptureContext& context) override;
};
#endif // FLAMESHOT_IMGUPLOADERMANAGER_H
