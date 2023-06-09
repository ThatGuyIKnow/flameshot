// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Yurii Puchkov & Contributors
//

#include "ocrtool.h"
#include "abstractlogger.h"
#include "flameshotdaemon.h"
#include "tesseract_tool.h"
#include <QPainter>
#include <QPixmap>
#include <QWidget>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

OCRTool::OCRTool(QObject* parent)
  : AbstractActionTool(parent)
{}

bool OCRTool::closeOnButtonPressed() const
{
    return true;
}

QIcon OCRTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "ocr.svg");
}
QString OCRTool::name() const
{
    return tr("Save");
}

CaptureTool::Type OCRTool::type() const
{
    return CaptureTool::TYPE_OCR;
}

QString OCRTool::description() const
{
    return "Copy OCR to Clipboard";
}

CaptureTool* OCRTool::copy(QObject* parent)
{
    return new OCRTool(parent);
}

void OCRTool::pressed(CaptureContext& context)
{
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        AbstractLogger::info() << "Could not initialize tesseract.";
        exit(1);
    }
    emit requestAction(REQ_CAPTURE_DONE_OK);
    emit requestAction(REQ_CLOSE_GUI);

    // Open input image with leptonica library
    Pix* image =
      TesseractTool::qImageToPIX(context.selectedScreenshotArea().toImage());
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    FlameshotDaemon::copyToClipboard(outText, outText);

    // Destroy used object and release memory
    api->End();
    delete api;
}
