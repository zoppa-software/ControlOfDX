#include "stdafx.h"
#include <vcclr.h>  
#include "VisualRenderTarget.h"

namespace ControlOfDX
{
    //-----------------------------------------------------------------------------
    // À•W•ÏŠ·
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::SetTransform()
    {
        this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    void VisualRenderTarget::SetTransform(int offsetX, int offsetY)
    {
        this->renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF((float)offsetX, (float)offsetY)));
    }

    void VisualRenderTarget::SetTransform(Matrix matrix)
    {
        this->renderTarget->SetTransform(matrix.Convert());
    }

    void VisualRenderTarget::PushAxisAlignedClip(RectangleF rect, AntialiasMode mode)
    {
        D2D1_RECT_F rec = D2D1::RectF((float)rect.Left,
                                      (float)rect.Top,
                                      (float)rect.Right,
                                      (float)rect.Bottom);
        this->renderTarget->PushAxisAlignedClip(rec, (D2D1_ANTIALIAS_MODE)mode);
    }

    void VisualRenderTarget::PopAxisAlignedClip()
    {
        this->renderTarget->PopAxisAlignedClip();
    }

    //-----------------------------------------------------------------------------
    // ‡¬Ý’è
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::SetAntialiasMode(AntialiasMode mode)
    {
        this->renderTarget->SetAntialiasMode((D2D1_ANTIALIAS_MODE)mode);
    }

    //-----------------------------------------------------------------------------
    // ”wŒiFƒNƒŠƒA
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::Clear(Color color)
    {
        D2D1::ColorF clr = D2D1::ColorF(color.R / 255.0f,
            color.G / 255.0f,
            color.B / 255.0f,
            color.A / 255.0f);
        this->renderTarget->Clear(clr);
    }

    void VisualRenderTarget::Clear(int red, int green, int blue, int alpha)
    {
        D2D1::ColorF clr = D2D1::ColorF(red / 255.0f,
            green / 255.0f,
            blue / 255.0f,
            alpha / 255.0f);
        this->renderTarget->Clear(clr);
    }

    //-----------------------------------------------------------------------------
    // ƒŒƒCƒ„[§Œä
    //-----------------------------------------------------------------------------
    Layer ^ VisualRenderTarget::CreateLayer()
    {
        ID2D1Layer * layer = NULL;
        HRESULT hr = this->renderTarget->CreateLayer(&layer);
        return (SUCCEEDED(hr) ? gcnew Layer(layer) : gcnew Layer());
    }

    Layer ^ VisualRenderTarget::CreateLayer(SizeF size)
    {
        ID2D1Layer * layer = NULL;
        D2D1_SIZE_F sz = D2D1::SizeF(size.Width, size.Height);
        HRESULT hr = this->renderTarget->CreateLayer(sz, &layer);
        return (SUCCEEDED(hr) ? gcnew Layer(layer) : gcnew Layer());
    }

    void VisualRenderTarget::PushLayer(Layer ^ layer)
    {
        D2D1_LAYER_PARAMETERS prm;
        Layer::LayerParameters ^ src = layer->Parameters;
        prm.contentBounds = (src->ContentBounds.Left == FLT_MIN &&
            src->ContentBounds.Top == FLT_MIN &&
            src->ContentBounds.Width == FLT_MAX &&
            src->ContentBounds.Height == FLT_MAX) ?
            D2D1::InfiniteRect() :
            D2D1::RectF(src->ContentBounds.Left,
                src->ContentBounds.Top,
                src->ContentBounds.Right,
                src->ContentBounds.Bottom);
        prm.geometricMask = src->GeometricMask != nullptr ?
            (ID2D1Geometry*)src->GeometricMask->GetInstance() : NULL;
        prm.maskAntialiasMode = (D2D1_ANTIALIAS_MODE)src->MaskAntialiasMode;
        prm.maskTransform = src->MaskTransform.Convert();
        prm.opacity = src->Opacity;
        prm.opacityBrush = src->OpacityBrush != nullptr ?
            (ID2D1Brush*)src->OpacityBrush->GetInstance() : NULL;
        prm.layerOptions = (D2D1_LAYER_OPTIONS)src->LayerOptions;
        this->renderTarget->PushLayer(prm, layer->GetInstance());
    }

    void VisualRenderTarget::PopLayer()
    {
        this->renderTarget->PopLayer();
    }

    //-----------------------------------------------------------------------------
    // •`‰æAPI
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        float opacity,
                                        BitmapInterpolationMode interpolationMode,
                                        RectangleF sourceRectangle)
    {
        if (bitmap != nullptr && bitmap->GetInstance() != NULL) {
            D2D1_RECT_F src = D2D1::RectF((float)sourceRectangle.Left,
                                          (float)sourceRectangle.Top,
                                          (float)sourceRectangle.Right,
                                          (float)sourceRectangle.Bottom);
            this->renderTarget->DrawBitmap((ID2D1Bitmap*)bitmap->GetInstance(), NULL,
                opacity, (D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode, &src);
        }
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        BitmapInterpolationMode interpolationMode,
                                        RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, destinationRectangle, 1, interpolationMode, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        float opacity,
                                        RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, destinationRectangle, opacity,
            BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        float opacity,
                                        BitmapInterpolationMode interpolationMode)
    {
        if (bitmap != nullptr && bitmap->GetInstance() != NULL) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);
            this->renderTarget->DrawBitmap((ID2D1Bitmap*)bitmap->GetInstance(),
                &dest, opacity, (D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode);
        }
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        float opacity,
                                        BitmapInterpolationMode interpolationMode,
                                        RectangleF sourceRectangle)
    {
        if (bitmap != nullptr && bitmap->GetInstance() != NULL) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);
            D2D1_RECT_F src = D2D1::RectF((float)sourceRectangle.Left,
                                          (float)sourceRectangle.Top,
                                          (float)sourceRectangle.Right,
                                          (float)sourceRectangle.Bottom);
            this->renderTarget->DrawBitmap((ID2D1Bitmap*)bitmap->GetInstance(),
                &dest, opacity, (D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode, &src);
        }
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        float opacity)
    {
        this->DrawBitmap(bitmap, destinationRectangle, opacity, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        BitmapInterpolationMode interpolationMode)
    {
        this->DrawBitmap(bitmap, destinationRectangle, 1, interpolationMode);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        float opacity,
                                        BitmapInterpolationMode interpolationMode)
    {
        if (bitmap != nullptr && bitmap->GetInstance() != NULL) {
            this->renderTarget->DrawBitmap((ID2D1Bitmap*)bitmap->GetInstance(),
                            NULL, opacity, (D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode);
        }
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        RectangleF destinationRectangle,
                                        RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, destinationRectangle, 1, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        float opacity,
                                        RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, opacity, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        BitmapInterpolationMode interpolationMode,
                                        RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, 1, interpolationMode, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap, RectangleF destinationRectangle)
    {
        this->DrawBitmap(bitmap, destinationRectangle, 1, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap, float opacity)
    {
        this->DrawBitmap(bitmap, opacity, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap,
                                        BitmapInterpolationMode interpolationMode)
    {
        this->DrawBitmap(bitmap, 1, interpolationMode);
    }

    void VisualRenderTarget::DrawBitmapSource(VisualResource ^ bitmap,
                                              RectangleF sourceRectangle)
    {
        this->DrawBitmap(bitmap, 1, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR, sourceRectangle);
    }

    void VisualRenderTarget::DrawBitmap(VisualResource ^ bitmap)
    {
        this->DrawBitmap(bitmap, 1, BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_LINEAR);
    }

    void VisualRenderTarget::DrawEllipse(RectangleF rect, VisualResource ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(rect.Left, rect.Top), rect.Width, rect.Height);
            this->renderTarget->DrawEllipse(ellipse, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawEllipse(RectangleF rect, VisualResource ^ brush, float strokeWidth, VisualResource ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(rect.Left, rect.Top), rect.Width, rect.Height);
            this->renderTarget->DrawEllipse(ellipse, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    void VisualRenderTarget::DrawEllipse(Ellipse ellipse, VisualResource ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                              (float)ellipse.RadiusX,
                                              (float)ellipse.RadiusY);
            this->renderTarget->DrawEllipse(ellp, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawEllipse(Ellipse ellipse, VisualResource ^ brush, float strokeWidth, VisualResource ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                              (float)ellipse.RadiusX,
                                              (float)ellipse.RadiusY);
            this->renderTarget->DrawEllipse(ellp, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    void VisualRenderTarget::DrawGeometry(VisualResource ^ geometry,
                                          VisualResource ^ brush,
                                          float strokeWidth)
    {
        if (geometry != nullptr && brush != nullptr) {
            this->renderTarget->DrawGeometry((ID2D1Geometry*)geometry->GetInstance(),
                                             (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawGeometry(VisualResource ^ geometry,
                                          VisualResource ^ brush,
                                          float strokeWidth,
                                          VisualResource ^ strokeStyle)
    {
        if (geometry != nullptr && brush != nullptr) {
            this->renderTarget->DrawGeometry((ID2D1Geometry*)geometry->GetInstance(),
                                             (ID2D1Brush*)brush->GetInstance(),
                                             strokeWidth,
                                             (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    //this->renderTarget->DrawGlyphRun;

    void VisualRenderTarget::DrawLine(PointF startPt, PointF endPt, VisualResource ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_POINT_2F pos1 = D2D1::Point2F(startPt.X, startPt.Y);
            D2D1_POINT_2F pos2 = D2D1::Point2F(endPt.X, endPt.Y);
            this->renderTarget->DrawLine(pos1, pos2, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawLine(PointF startPt, PointF endPt, VisualResource ^ brush, float strokeWidth, VisualResource ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_POINT_2F pos1 = D2D1::Point2F(startPt.X, startPt.Y);
            D2D1_POINT_2F pos2 = D2D1::Point2F(endPt.X, endPt.Y);
            this->renderTarget->DrawLine(pos1, pos2, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    void VisualRenderTarget::DrawRectangle(RectangleF rectangle, VisualResource ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                (float)rectangle.Top,
                (float)rectangle.Right,
                (float)rectangle.Bottom);
            this->renderTarget->DrawRectangle(rec, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawRectangle(RectangleF rectangle, VisualResource ^ brush, float strokeWidth, VisualResource ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                (float)rectangle.Top,
                (float)rectangle.Right,
                (float)rectangle.Bottom);
            this->renderTarget->DrawRectangle(rec, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    //this->renderTarget->DrawRoundedRectangle;

    void VisualRenderTarget::DrawText(String ^ text, VisualResource ^ format, RectangleF rect, VisualResource ^ brush)
    {
        if (format != nullptr && brush != nullptr) {
            pin_ptr<const wchar_t> txt = (text != nullptr ? PtrToStringChars(text) : (WCHAR*)NULL);
            D2D1_RECT_F rec = D2D1::RectF(rect.Left, rect.Top, rect.Right, rect.Bottom);

            this->renderTarget->DrawText(txt, text->Length,
                (IDWriteTextFormat*)format->GetWriteInstance(), rec, (ID2D1Brush*)brush->GetInstance());
        }
    }

    //this->renderTarget->DrawTextLayout;
    //this->renderTarget->FillRoundedRectangle;

    void VisualRenderTarget::FillEllipse(Ellipse ellipse, VisualResource ^ brush)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                (float)ellipse.RadiusX,
                (float)ellipse.RadiusY);
            this->renderTarget->FillEllipse(ellp, (ID2D1Brush*)brush->GetInstance());
        }
    }

    void VisualRenderTarget::FillGeometry(VisualResource ^ geometry, VisualResource ^ brush)
    {
        if (brush != nullptr && geometry->GetInstance() != NULL) {
            this->renderTarget->FillGeometry((ID2D1Geometry*)geometry->GetInstance(),
                                             (ID2D1Brush*)brush->GetInstance());
        }
    }

    void VisualRenderTarget::FillGeometry(VisualResource ^ geometry,
                                          VisualResource ^ brush,
                                          VisualResource ^ opacitybrush)
    {
        if (brush != nullptr && geometry->GetInstance() != NULL) {
            this->renderTarget->FillGeometry((ID2D1Geometry*)geometry->GetInstance(),
                                             (ID2D1Brush*)brush->GetInstance(),
                                             (ID2D1Brush*)opacitybrush->GetInstance());
        }
    }

    //this->renderTarget->FillMesh;

    void VisualRenderTarget::FillOpacityMask(VisualResource ^ bitmap,
                                             VisualResource ^ brush,
                                             OpacityMaskContent opacityMask)
    {
        if (bitmap != nullptr && brush != nullptr) {
            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask);
        }
    }

    void VisualRenderTarget::FillOpacityMask(VisualResource ^ bitmap,
                                             VisualResource ^ brush,
                                             OpacityMaskContent opacityMask,
                                             RectangleF destinationRectangle)
    {
        if (bitmap != nullptr && brush != nullptr) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);

            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask,
                                                &dest);
        }
    }

    void VisualRenderTarget::FillOpacityMask(VisualResource ^ bitmap,
                                             VisualResource ^ brush,
                                             OpacityMaskContent opacityMask,
                                             RectangleF destinationRectangle,
                                             RectangleF sourceRectangle)
    {
        if (bitmap != nullptr && brush != nullptr) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);
            D2D1_RECT_F src = D2D1::RectF((float)sourceRectangle.Left,
                                          (float)sourceRectangle.Top,
                                          (float)sourceRectangle.Right,
                                          (float)sourceRectangle.Bottom);

            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask,
                                                &dest, &src);
        }
    }

    void VisualRenderTarget::FillRectangle(RectangleF rectangle, VisualResource ^ brush)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                (float)rectangle.Top,
                (float)rectangle.Right,
                (float)rectangle.Bottom);
            this->renderTarget->FillRectangle(rec, (ID2D1Brush*)brush->GetInstance());
        }
    }

    //this->renderTarget->FillRoundedRectangle;
}