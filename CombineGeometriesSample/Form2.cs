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

            var pathGeometryIntersect = this.mainControl.Resources.CreatePathGeometry("PathGeometryIntersect");
            using (var sink = pathGeometryIntersect.CreateGeometrySink()) {
                circleGeometry1.CombineWithGeometry(circleGeometry2, ControlOfDX.CombineMode.COMBINE_MODE_INTERSECT, sink);
            }

            var pathGeometryXor = this.mainControl.Resources.CreatePathGeometry("PathGeometryXor");
            using (var sink = pathGeometryXor.CreateGeometrySink()) {
                circleGeometry1.CombineWithGeometry(circleGeometry2, ControlOfDX.CombineMode.COMBINE_MODE_XOR, sink);
            }

            var pathGeometryExclude = this.mainControl.Resources.CreatePathGeometry("PathGeometryExclude");
            using (var sink = pathGeometryExclude.CreateGeometrySink()) {
                circleGeometry1.CombineWithGeometry(circleGeometry2, ControlOfDX.CombineMode.COMBINE_MODE_EXCLUDE, sink);
            }

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
            e.RenderTarget.SetTransform();
            e.RenderTarget.Clear(Color.White);

            // 背景処理
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.Width, this.Height), e.Resources["GridPatternBitmapBrush"]);

            // 結合前ジオメトリ描画
            e.RenderTarget.FillGeometry(e.Resources["CircleGeometry1"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["CircleGeometry1"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.FillGeometry(e.Resources["CircleGeometry2"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["CircleGeometry2"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.DrawText("The circles before combining", e.Resources["format"], new RectangleF(25, 130, 175, 100), e.Resources["TextBrush"]);

            // 結合ジオメトリ描画
            e.RenderTarget.SetTransform(200, 0);
            e.RenderTarget.FillGeometry(e.Resources["PathGeometryUnion"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["PathGeometryUnion"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.DrawText("D2D1_COMBINE_MODE_UNION", e.Resources["format"], new RectangleF(25, 130, 175, 100), e.Resources["TextBrush"]);

            // 共通部ジオメトリ描画
            e.RenderTarget.SetTransform(400, 0);
            e.RenderTarget.FillGeometry(e.Resources["PathGeometryIntersect"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["PathGeometryIntersect"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.DrawText("D2D1_COMBINE_MODE_INTERSECT", e.Resources["format"], new RectangleF(25, 130, 200, 100), e.Resources["TextBrush"]);

            // 排他ジオメトリ描画
            e.RenderTarget.SetTransform(200, 150);
            e.RenderTarget.FillGeometry(e.Resources["PathGeometryXor"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["PathGeometryXor"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.DrawText("D2D1_COMBINE_MODE_XOR", e.Resources["format"], new RectangleF(25, 130, 200, 100), e.Resources["TextBrush"]);

            // 以外ジオメトリ描画
            e.RenderTarget.SetTransform(400, 150);
            e.RenderTarget.FillGeometry(e.Resources["PathGeometryExclude"], e.Resources["ShapeFillBrush"]);
            e.RenderTarget.DrawGeometry(e.Resources["PathGeometryExclude"], e.Resources["OutlineBrush"], 1);
            e.RenderTarget.DrawText("D2D1_COMBINE_MODE_EXCLUDE", e.Resources["format"], new RectangleF(25, 130, 200, 100), e.Resources["TextBrush"]);

            var circleGeometry1 = (VisualResourceOfGeometry)e.Resources["CircleGeometry1"];
            var circleGeometry2 = (VisualResourceOfGeometry)e.Resources["CircleGeometry2"];

            // 次のコードは、さまざまな幾何学的操作を呼び出す方法を示しています。 ニーズに応じて、これらの出力値の使用方法を決定できます。
            var result = circleGeometry1.CompareWithGeometry(circleGeometry2, Matrix.Identity(), 1);
            if (result == GeometryRelation.GEOMETRY_RELATION_OVERLAP) {
                e.RenderTarget.DrawText("Two circles overlap.", e.Resources["format"], new RectangleF(25, 160, 200, 100), e.Resources["TextBrush"]);
            }

            var area = circleGeometry1.ComputeArea(Matrix.Identity());
            var length = circleGeometry1.ComputeLength(Matrix.Identity());
            /*

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
        }
    }
}