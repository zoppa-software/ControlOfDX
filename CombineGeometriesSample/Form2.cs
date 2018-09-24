using System;
using System.Drawing;
using System.Windows.Forms;
using ControlOfDX;

namespace DrawRectangleExample
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void mainlControl_InitializeResource(object sender, EventArgs e)
        {
            // フォント設定
            var format = this.mainControl.Resources.CreateTextFormat("format");
            format.FontFamilyName = "Verdana";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_REGULAR;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontStretch = DWriteFontStretch.DWRITE_FONT_STRETCH_NORMAL;
            format.FontSize = 10.0f;

            // ストローク設定
            var stroke = this.mainControl.Resources.CreateStrokeStyle("stoke");
            stroke.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            stroke.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            stroke.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            stroke.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            stroke.Properties.MiterLimit = 10.0f;
            stroke.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            stroke.Properties.DashOffset = 0;
            stroke.DashesAddRange(new float[] { 1, 1, 2, 3, 5 });

            // ジオメトリ
            var circleGeometry1 = this.mainControl.Resources.CreateEllipseGeometry("CircleGeometry1", new PointF(75, 75), 50, 50);
            var circleGeometry2 = this.mainControl.Resources.CreateEllipseGeometry("CircleGeometry2", new PointF(125, 75), 50, 50);

            var pathGeometryUnion = this.mainControl.Resources.CreatePathGeometry("PathGeometryUnion");
            using (var sink = pathGeometryUnion.CreateGeometrySink()) {
                circleGeometry1.CombineWithGeometry(circleGeometry2, ControlOfDX.CombineMode.COMBINE_MODE_UNION, sink);
            }

            /*
            if (SUCCEEDED(hr)) {
                //
                // Use D2D1_COMBINE_MODE_INTERSECT to combine the geometries.
                //
                hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometryIntersect);

                if (SUCCEEDED(hr)) {
                    hr = m_pPathGeometryIntersect->Open(&pGeometrySink);

                    if (SUCCEEDED(hr)) {
                        hr = m_pCircleGeometry1->CombineWithGeometry(
                            m_pCircleGeometry2,
                            D2D1_COMBINE_MODE_INTERSECT,
                            NULL,
                            NULL,
                            pGeometrySink
                            );
                    }

                    if (SUCCEEDED(hr)) {
                        hr = pGeometrySink->Close();
                    }

                    SafeRelease(&pGeometrySink);
                }
            }

            if (SUCCEEDED(hr)) {
                //
                // Use D2D1_COMBINE_MODE_XOR to combine the geometries.
                //
                hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometryXOR);

                if (SUCCEEDED(hr)) {
                    hr = m_pPathGeometryXOR->Open(&pGeometrySink);

                    if (SUCCEEDED(hr)) {
                        hr = m_pCircleGeometry1->CombineWithGeometry(
                            m_pCircleGeometry2,
                            D2D1_COMBINE_MODE_XOR,
                            NULL,
                            NULL,
                            pGeometrySink
                            );
                    }

                    if (SUCCEEDED(hr)) {
                        hr = pGeometrySink->Close();
                    }

                    SafeRelease(&pGeometrySink);
                }
            }

            if (SUCCEEDED(hr)) {
                //
                // Use D2D1_COMBINE_MODE_EXCLUDE to combine the geometries.
                //
                hr = m_pD2DFactory->CreatePathGeometry(&m_pPathGeometryExclude);

                if (SUCCEEDED(hr)) {
                    hr = m_pPathGeometryExclude->Open(&pGeometrySink);

                    if (SUCCEEDED(hr)) {
                        hr = m_pCircleGeometry1->CombineWithGeometry(
                            m_pCircleGeometry2,
                            D2D1_COMBINE_MODE_EXCLUDE,
                            NULL,
                            NULL,
                            pGeometrySink
                            );
                    }

                    if (SUCCEEDED(hr)) {
                        hr = pGeometrySink->Close();
                    }

                    SafeRelease(&pGeometrySink);
                }
            }

            /*
            var ellipseGeometry = this.mainControl.Resources.CreateEllipseGeometry("ellipseGeometry", new PointF(100, 60), 100, 50);

            var pathGeometry = this.mainControl.Resources.CreatePathGeometry("pathGeometry");
            using (var sink = pathGeometry.CreateGeometrySink()) {
                sink.BeginFigure(new PointF(10, 50), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddBezier(new PointF(100, 0), new PointF(200,200), new PointF(300,100));
                sink.AddLine(400, 100);
                sink.AddArc(new PointF(200, 100), new SizeF(50, 50), 30, SweepDirection.SWEEP_DIRECTION_COUNTER_CLOCKWISE, ArcSize.ARC_SIZE_LARGE);
                sink.AddBezier(new PointF(150, 50), new PointF(100, 150), new PointF(0, 0));
                sink.EndFigure(FigureEnd.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(10, 300), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddBezier(new PointF(100, 250), new PointF(200, 450), new PointF(300, 350));
                sink.AddLine(400, 350);
                sink.AddArc(new PointF(200, 350), new SizeF(50, 50), 30, SweepDirection.SWEEP_DIRECTION_COUNTER_CLOCKWISE, ArcSize.ARC_SIZE_LARGE);
                sink.AddBezier(new PointF(150, 300), new PointF(100, 400), new PointF(0, 250));
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            var pathGeometry1 = this.mainControl.Resources.CreatePathGeometry("pathGeometry1");
            using (var sink = pathGeometry1.CreateGeometrySink()) {
                sink.BeginFigure(new PointF(0, 0), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddLines(new PointF[] {
                    new PointF(200, 0),
                    new PointF(300, 200),
                    new PointF(100, 200),
                });
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            // 黒ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("brush", Color.Black);

            using (var bmp = new Bitmap(10, 10)) {
                using (var brh = new SolidBrush(Color.FromArgb(255, 237, 239, 245))) {
                    using (var g = Graphics.FromImage(bmp)) {
                        g.Clear(Color.White);
                        g.FillRectangle(brh, 0, 0, 10, 1);
                        g.FillRectangle(brh, 0, 0, 1, 10);
                    }
                    this.mainControl.Resources.CreateBitmapBrush("GridPatternBitmapBrush", bmp);
                }
            }
            */

            // ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("OutlineBrush", Color.DarkSlateBlue);
            this.mainControl.Resources.CreateSolidColorBrush("ShapeFillBrush", Color.FromArgb(128, Color.CornflowerBlue.R, Color.CornflowerBlue.G, Color.CornflowerBlue.B));
            this.mainControl.Resources.CreateSolidColorBrush("TextBrush", Color.Black);

            using (var bmp = new Bitmap(10, 10)) {
                using (var brh = new SolidBrush(Color.FromArgb(255, 237, 239, 245))) {
                    using (var g = Graphics.FromImage(bmp)) {
                        g.Clear(Color.White);
                        g.FillRectangle(brh, 0, 0, 10, 1);
                        g.FillRectangle(brh, 0, 0, 1, 10);
                    }
                    this.mainControl.Resources.CreateBitmapBrush("GridPatternBitmapBrush", bmp);
                }
            }
        }

        private void mainlControl_Rendering(object sender, ControlOfDX.VisualRenderEventArgs e)
        {
            /*
             *         static const WCHAR szBeforeText[] = L"The circles before combining";
        static const WCHAR szUnionText[] = L"D2D1_COMBINE_MODE_UNION";
        static const WCHAR szIntersectText[] = L"D2D1_COMBINE_MODE_INTERSECT";
        static const WCHAR szXorText[] = L"D2D1_COMBINE_MODE_XOR";
        static const WCHAR szExcludeText[] = L"D2D1_COMBINE_MODE_EXCLUDE";

        m_pRenderTarget->BeginDraw();
        */
            e.RenderTarget.SetTransform();
            e.RenderTarget.Clear(Color.White);
            /*
        D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();

        m_pRenderTarget->FillRectangle(
            D2D1::RectF(0.f, 0.f, renderTargetSize.width, renderTargetSize.height),
            m_pGridPatternBitmapBrush
            );

        // Draw the geomtries before merging.
        m_pRenderTarget->FillGeometry(m_pCircleGeometry1, m_pShapeFillBrush);
        m_pRenderTarget->DrawGeometry(m_pCircleGeometry1, m_pOutlineBrush, 1.0f);
        m_pRenderTarget->FillGeometry(m_pCircleGeometry2, m_pShapeFillBrush);
        m_pRenderTarget->DrawGeometry(m_pCircleGeometry2, m_pOutlineBrush, 1.0f);

        m_pRenderTarget->DrawText(
            szBeforeText,
            ARRAYSIZE(szBeforeText) - 1,
            m_pTextFormat,
            D2D1::RectF(25.0f, 130.0f, 200.0f, 300.0f),
            m_pTextBrush
            );
  
        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(200, 0));
        */
            // Draw the geometries merged using the union combine mode.
            e.RenderTarget.FillGeometry(e.Resources["PathGeometryUnion"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["PathGeometryUnion"], e.Resources["OutlineBrush"], 1);
            /*
        m_pRenderTarget->DrawText(
            szUnionText,
            ARRAYSIZE(szUnionText) - 1,
            m_pTextFormat,
            D2D1::RectF(25, 130, 200, 300),
            m_pTextBrush
            );

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(400, 0));

        // Draw the geometries merged using the intersect combine mode.
        m_pRenderTarget->FillGeometry(m_pPathGeometryIntersect, m_pShapeFillBrush, NULL);
        m_pRenderTarget->DrawGeometry(m_pPathGeometryIntersect, m_pOutlineBrush, 1.0f);

        m_pRenderTarget->DrawText(
            szIntersectText,
            ARRAYSIZE(szIntersectText) - 1,
            m_pTextFormat,
            D2D1::RectF(25, 130, 400, 300),
            m_pTextBrush
            );

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(200, 150));

        // Draw the geometries merged using the XOR combine mode.
        m_pRenderTarget->FillGeometry(m_pPathGeometryXOR, m_pShapeFillBrush, NULL);
        m_pRenderTarget->DrawGeometry(m_pPathGeometryXOR, m_pOutlineBrush, 1.0f);

        m_pRenderTarget->DrawText(
            szXorText,
            ARRAYSIZE(szXorText) - 1,
            m_pTextFormat,
            D2D1::RectF(25, 130, 200, 470),
            m_pTextBrush
            );

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(400, 150));

        // Draw the geometries merged using the exclude combine mode.
        m_pRenderTarget->FillGeometry(m_pPathGeometryExclude, m_pShapeFillBrush, NULL);
        m_pRenderTarget->DrawGeometry(m_pPathGeometryExclude, m_pOutlineBrush, 1.0f);

        m_pRenderTarget->DrawText(
            szExcludeText,
            ARRAYSIZE(szExcludeText) - 1,
            m_pTextFormat,
            D2D1::RectF(25, 130, 400, 470),
            m_pTextBrush
            );

        // The following code demonstrates how to call various geometric operations. Depending on 
        // your needs, it lets you decide how to use those output values.
        D2D1_GEOMETRY_RELATION result = D2D1_GEOMETRY_RELATION_UNKNOWN;

        // Compare circle1 with circle2
        hr = m_pCircleGeometry1->CompareWithGeometry(
            m_pCircleGeometry2,
            D2D1::IdentityMatrix(),
            0.1f,
            &result
            );

        if (SUCCEEDED(hr))
        {
            static const WCHAR szGeometryRelation[] = L"Two circles overlap.";
            m_pRenderTarget->SetTransform(D2D1::IdentityMatrix());
            if (result == D2D1_GEOMETRY_RELATION_OVERLAP)
            {
                m_pRenderTarget->DrawText(
                    szGeometryRelation,
                    ARRAYSIZE(szGeometryRelation) - 1,
                    m_pTextFormat,
                    D2D1::RectF(25.0f, 160.0f, 200.0f, 300.0f),
                    m_pTextBrush
                    );
            }
        }

        float area;

        // Compute the area of circle1
        hr = m_pCircleGeometry1->ComputeArea(
            D2D1::IdentityMatrix(),
            &area
            );

        float length;

        // Compute the area of circle1
        hr = m_pCircleGeometry1->ComputeLength(
            D2D1::IdentityMatrix(),
            &length
            );

        if (SUCCEEDED(hr))
        {
            // Process the length of the geometry.
        }

        D2D1_POINT_2F point;
        D2D1_POINT_2F tangent;

        hr = m_pCircleGeometry1->ComputePointAtLength(
            10, 
            NULL, 
            &point, 
            &tangent); 

        if (SUCCEEDED(hr))
        {
            // Retrieve the point and tangent point.
        }

        D2D1_RECT_F bounds;

        hr = m_pCircleGeometry1->GetBounds(
              D2D1::IdentityMatrix(),
              &bounds
             );

        if (SUCCEEDED(hr))
        {
            // Retrieve the bounds.
        }

        D2D1_RECT_F bounds1;
        hr = m_pCircleGeometry1->GetWidenedBounds(
              5.0,
              m_pStrokeStyle,
              D2D1::IdentityMatrix(),
              &bounds1
             );
        if (SUCCEEDED(hr))
        {
            // Retrieve the widened bounds.
        }

        BOOL containsPoint;
        
        hr = m_pCircleGeometry1->StrokeContainsPoint(
            D2D1::Point2F(0,0),
            10,     // stroke width
            NULL,   // stroke style
            NULL,   // world transform
            &containsPoint
            );

        if (SUCCEEDED(hr))
        {
            // Process containsPoint.
        }

        BOOL containsPoint1;
        hr = m_pCircleGeometry1->FillContainsPoint(
            D2D1::Point2F(0,0),
            D2D1::Matrix3x2F::Identity(),
            &containsPoint1
            );

        if (SUCCEEDED(hr))
        {
            // Process containsPoint.
        }
             */
            /*
            e.RenderTarget.SetTransform();
            e.RenderTarget.Clear(Color.White);
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.Width, this.Height), e.Resources["GridPatternBitmapBrush"]);

            e.RenderTarget.SetTransform(10, 10);
            e.RenderTarget.DrawGeometry(e.Resources["pathGeometry"], e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 65);
            e.RenderTarget.DrawEllipse(new Ellipse(new PointF(100, 60), 100, 50), e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 5);
            e.RenderTarget.DrawGeometry(e.Resources["ellipseGeometry"], e.Resources["brush"], 5);

            e.RenderTarget.SetTransform(500, 200);
            e.RenderTarget.DrawGeometry(e.Resources["pathGeometry1"], e.Resources["brush"], 5);
            */
        }
    }
}