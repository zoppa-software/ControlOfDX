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
            // 黒ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("brush", Color.Black);

            // 青ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("cornflower blue", Color.CornflowerBlue);

            // フォント設定
            var format = this.mainControl.Resources.CreateTextFormat("text format");
            format.FontFamilyName = "yu gothic ui";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_REGULAR;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontSize = 14;

            // 背景ブラシ作成
            using (var bmp = new Bitmap(10, 10)) {
                using (var g = Graphics.FromImage(bmp)) {
                    g.Clear(Color.White);
                    g.DrawLine(Pens.WhiteSmoke, 0, 0, 10, 0);
                    g.DrawLine(Pens.WhiteSmoke, 0, 0, 0, 10);
                }
                this.mainControl.Resources.CreateBitmapBrush("grid pattern", (Bitmap)bmp.Clone());
            }

            var strokeStyleSolidMiter = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidMiter");
            strokeStyleSolidMiter.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleSolidMiter.Properties.MiterLimit = 2;
            strokeStyleSolidMiter.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidMiter.Properties.DashOffset = 0;

            var strokeStyleSolidBevel = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidBevel");
            strokeStyleSolidBevel.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.LineJoin = LineJoin.LINE_JOIN_BEVEL;
            strokeStyleSolidBevel.Properties.MiterLimit = 2;
            strokeStyleSolidBevel.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidBevel.Properties.DashOffset = 0;

            var strokeStyleSolidMiterOrBevel = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidMiterOrBevel");
            strokeStyleSolidMiterOrBevel.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.LineJoin = LineJoin.LINE_JOIN_MITER_OR_BEVEL;
            strokeStyleSolidMiterOrBevel.Properties.MiterLimit = 2;
            strokeStyleSolidMiterOrBevel.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidMiterOrBevel.Properties.DashOffset = 0;

            var strokeStyleSolidRoundwRoundCap = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidRoundwRoundCap");
            strokeStyleSolidRoundwRoundCap.Properties.StartCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.EndCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwRoundCap.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.MiterLimit = 2;
            strokeStyleSolidRoundwRoundCap.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwRoundCap.Properties.DashOffset = 0;

            var strokeStyleSolidRoundwFlatCap = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidRoundwFlatCap");
            strokeStyleSolidRoundwFlatCap.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwFlatCap.Properties.MiterLimit = 2;
            strokeStyleSolidRoundwFlatCap.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwFlatCap.Properties.DashOffset = 0;

            var strokeStyleSolidRoundwSquareCap = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidRoundwSquareCap");
            strokeStyleSolidRoundwSquareCap.Properties.StartCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleSolidRoundwSquareCap.Properties.EndCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleSolidRoundwSquareCap.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwSquareCap.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwSquareCap.Properties.MiterLimit = 2;
            strokeStyleSolidRoundwSquareCap.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwSquareCap.Properties.DashOffset = 0;

            var strokeStyleSolidRoundwTriangleCap = this.mainControl.Resources.CreateStrokeStyle("strokeStyleSolidRoundwTriangleCap");
            strokeStyleSolidRoundwTriangleCap.Properties.StartCap = CapStyle.CAP_STYLE_TRIANGLE;
            strokeStyleSolidRoundwTriangleCap.Properties.EndCap = CapStyle.CAP_STYLE_TRIANGLE;
            strokeStyleSolidRoundwTriangleCap.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwTriangleCap.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwTriangleCap.Properties.MiterLimit = 2;
            strokeStyleSolidRoundwTriangleCap.Properties.DashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwTriangleCap.Properties.DashOffset = 0;

            var strokeStyleDash = this.mainControl.Resources.CreateStrokeStyle("strokeStyleDash");
            strokeStyleDash.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDash.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDash.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDash.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDash.Properties.MiterLimit = 10;
            strokeStyleDash.Properties.DashStyle = DashStyle.DASH_STYLE_DASH;
            strokeStyleDash.Properties.DashOffset = 0;

            var strokeStyleDot = this.mainControl.Resources.CreateStrokeStyle("strokeStyleDot");
            strokeStyleDot.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDot.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDot.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDot.Properties.LineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleDot.Properties.MiterLimit = 10;
            strokeStyleDot.Properties.DashStyle = DashStyle.DASH_STYLE_DOT;
            strokeStyleDot.Properties.DashOffset = 0;

            var strokeStyleDashDot = this.mainControl.Resources.CreateStrokeStyle("strokeStyleDashDot");
            strokeStyleDashDot.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDot.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDot.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDashDot.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDashDot.Properties.MiterLimit = 10;
            strokeStyleDashDot.Properties.DashStyle = DashStyle.DASH_STYLE_DASH_DOT;
            strokeStyleDashDot.Properties.DashOffset = 0;

            var strokeStyleDashDotDot = this.mainControl.Resources.CreateStrokeStyle("strokeStyleDashDotDot");
            strokeStyleDashDotDot.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDotDot.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDotDot.Properties.DashCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleDashDotDot.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDashDotDot.Properties.MiterLimit = 10;
            strokeStyleDashDotDot.Properties.DashStyle = DashStyle.DASH_STYLE_DASH_DOT_DOT;
            strokeStyleDashDotDot.Properties.DashOffset = 0;

            // 点線パターン
            var dashes = new float[] { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };
            var strokeStyleCustomOffsetZero = this.mainControl.Resources.CreateStrokeStyle("strokeStyleCustomOffsetZero");
            strokeStyleCustomOffsetZero.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetZero.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetZero.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetZero.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetZero.Properties.MiterLimit = 10;
            strokeStyleCustomOffsetZero.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetZero.Properties.DashOffset = 0;
            strokeStyleCustomOffsetZero.DashesAddRange(dashes);

            var strokeStyleCustomOffsetNegOne = this.mainControl.Resources.CreateStrokeStyle("strokeStyleCustomOffsetNegOne");
            strokeStyleCustomOffsetNegOne.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegOne.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegOne.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetNegOne.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetNegOne.Properties.MiterLimit = 10;
            strokeStyleCustomOffsetNegOne.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetNegOne.Properties.DashOffset = -1;
            strokeStyleCustomOffsetNegOne.DashesAddRange(dashes);

            var strokeStyleCustomOffsetNegTwo = this.mainControl.Resources.CreateStrokeStyle("strokeStyleCustomOffsetNegTwo");
            strokeStyleCustomOffsetNegTwo.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegTwo.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegTwo.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetNegTwo.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetNegTwo.Properties.MiterLimit = 10;
            strokeStyleCustomOffsetNegTwo.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetNegTwo.Properties.DashOffset = -2;
            strokeStyleCustomOffsetNegTwo.DashesAddRange(dashes);

            var strokeStyleCustomOffsetPosOne = this.mainControl.Resources.CreateStrokeStyle("strokeStyleCustomOffsetPosOne");
            strokeStyleCustomOffsetPosOne.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosOne.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosOne.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetPosOne.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetPosOne.Properties.MiterLimit = 10;
            strokeStyleCustomOffsetPosOne.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetPosOne.Properties.DashOffset = 1;
            strokeStyleCustomOffsetPosOne.DashesAddRange(dashes);

            var strokeStyleCustomOffsetPosTwo = this.mainControl.Resources.CreateStrokeStyle("strokeStyleCustomOffsetPosTwo");
            strokeStyleCustomOffsetPosTwo.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosTwo.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosTwo.Properties.DashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetPosTwo.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetPosTwo.Properties.MiterLimit = 10;
            strokeStyleCustomOffsetPosTwo.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetPosTwo.Properties.DashOffset = 2;
            strokeStyleCustomOffsetPosTwo.DashesAddRange(dashes);

            var pathGeometry = this.mainControl.Resources.CreatePathGeometry("path geometry");
            using (var sink = pathGeometry.CreateGeometrySink()) {
                sink.SetFillMode(FillMode.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(17, 17), FigureBegin.FIGURE_BEGIN_HOLLOW);
                sink.AddLine(45, 85);
                sink.AddLine(85, 45);
                sink.AddLine(85, 125);
                sink.AddLine(165, 17);
                sink.EndFigure(FigureEnd.FIGURE_END_OPEN);
            }
        }

        private void mainlControl_Rendering(object sender, ControlOfDX.VisualRenderEventArgs e)
        {
            e.RenderTarget.SetTransform();

            // 背景クリア
            e.RenderTarget.Clear(Color.White);

            // 背景描画
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.mainControl.Width, this.mainControl.Height), e.Resources["grid pattern"]);

            // Line Join Styles
            e.RenderTarget.SetTransform(10, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidMiter"]);
            e.RenderTarget.DrawText("Miter Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(10, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidBevel"]);
            e.RenderTarget.DrawText("Bevel Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(230, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwRoundCap"]);
            e.RenderTarget.DrawText("Round Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(230, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidMiterOrBevel"]);
            e.RenderTarget.DrawText("Miter or Bevel Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            // Cap Styles
            e.RenderTarget.SetTransform(480, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwRoundCap"]);
            e.RenderTarget.DrawText("Round Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(700, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwFlatCap"]);
            e.RenderTarget.DrawText("Flat Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(480, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwSquareCap"]);
            e.RenderTarget.DrawText("Square Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(700, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwTriangleCap"]);
            e.RenderTarget.DrawText("Triangle Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            // Dash Styles
            e.RenderTarget.SetTransform(Matrix.Translation(10, 405));
            e.RenderTarget.DrawLine(new PointF(0, 10), new PointF(200, 10), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleSolidMiter"]);
            e.RenderTarget.DrawText("Dash Style -- Solid", e.Resources["text format"], new RectangleF(0, 20, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 70), new PointF(200, 70), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDash"]);
            e.RenderTarget.DrawText("Dash Style -- Dash", e.Resources["text format"], new RectangleF(0, 80, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 130), new PointF(200, 130), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dot", e.Resources["text format"], new RectangleF(0, 140, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 190), new PointF(200, 190), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDashDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dash Dot", e.Resources["text format"], new RectangleF(0, 200, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 250), new PointF(200, 250), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDashDotDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dash Dot Dot", e.Resources["text format"], new RectangleF(0, 260, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 310), new PointF(200, 310), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetZero"]);
            e.RenderTarget.DrawText("Dash Style -- Custom", e.Resources["text format"], new RectangleF(0, 320, 200, 315), e.Resources["brush"]);

            // Dash Offsets
            e.RenderTarget.SetTransform(Matrix.Translation(300, 405));
            e.RenderTarget.DrawLine(new PointF(0, 10), new PointF(200, 10), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetNegTwo"]);
            e.RenderTarget.DrawText("-2", e.Resources["text format"], new RectangleF(0, 20, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 70), new PointF(200, 70), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetNegOne"]);
            e.RenderTarget.DrawText("-1", e.Resources["text format"], new RectangleF(0, 80, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 130), new PointF(200, 130), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetZero"]);
            e.RenderTarget.DrawText("-0", e.Resources["text format"], new RectangleF(0, 140, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 190), new PointF(200, 190), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetPosOne"]);
            e.RenderTarget.DrawText("1", e.Resources["text format"], new RectangleF(0, 200, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 250), new PointF(200, 250), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetPosTwo"]);
            e.RenderTarget.DrawText("2", e.Resources["text format"], new RectangleF(0, 260, 200, 295), e.Resources["brush"]);
        }
    }
}