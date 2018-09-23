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
            var format = this.mainControl.Resources.CreateTextFormat("text format");
            format.FontFamilyName = "Verdana";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_REGULAR;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontStretch = DWriteFontStretch.DWRITE_FONT_STRETCH_NORMAL;
            format.FontSize = 13.0f;

            // ストローク設定
            var stroke = this.mainControl.Resources.CreateStrokeStyle("stoke");
            stroke.Properties.StartCap = CapStyle.CAP_STYLE_FLAT;
            stroke.Properties.EndCap = CapStyle.CAP_STYLE_FLAT;
            stroke.Properties.DashCap = CapStyle.CAP_STYLE_FLAT;
            stroke.Properties.LineJoin = LineJoin.LINE_JOIN_MITER;
            stroke.Properties.MiterLimit = 10.0f;
            stroke.Properties.DashStyle = DashStyle.DASH_STYLE_CUSTOM;
            stroke.Properties.DashOffset = 0;
            stroke.DashesAddRange(new float[] { 10.0f, 2.0f });

            // ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("OriginalShapeBrush", Color.DarkBlue);
            this.mainControl.Resources.CreateSolidColorBrush("FillBrush", Color.White);
            this.mainControl.Resources.CreateSolidColorBrush("TextBrush", Color.Black);
            this.mainControl.Resources.CreateSolidColorBrush("TransformedShapeBrush", Color.DarkBlue);

            // ビットマップブラシ
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

            // 背景消去
            e.RenderTarget.Clear(Color.White);

            //
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.ClientSize.Width, this.ClientSize.Height), e.Resources["GridPatternBitmapBrush"]);

            var originalShapeBrush = (VisualResourceOfSolidColorBrush)e.Resources["OriginalShapeBrush"];
            var fillBrush = (VisualResourceOfSolidColorBrush)e.Resources["FillBrush"];
            var stroke = (VisualResourceOfStrokeStyle)e.Resources["stoke"];
            var transformedShapeBrush = (VisualResourceOfSolidColorBrush)e.Resources["TransformedShapeBrush"];
            var format = (VisualResourceOfTextFormat)e.Resources["text format"];
            var textBrush = (VisualResourceOfSolidColorBrush)e.Resources["TextBrush"];

            originalShapeBrush.SetOpacity(128);
            fillBrush.SetOpacity(128);

            // 移動し、次に回転します。
            this.TranslationRotation(e.RenderTarget, originalShapeBrush, fillBrush, stroke, transformedShapeBrush, format, textBrush);

            // 回転し、次に移動します
            this.RotationTranslation(e.RenderTarget, originalShapeBrush, fillBrush, stroke, transformedShapeBrush, format, textBrush);
        }

        private void TranslationRotation(VisualRenderTarget render,
                                         VisualResourceOfSolidColorBrush originalShapeBrush,
                                         VisualResourceOfSolidColorBrush fillBrush,
                                         VisualResourceOfStrokeStyle stroke,
                                         VisualResourceOfSolidColorBrush transformedShapeBrush,
                                         VisualResourceOfTextFormat format,
                                         VisualResourceOfSolidColorBrush textBrush)
        {
            render.SetTransform();

            // 四角を作成
            var rectangle = new RectangleF(40.0f, 40.0f, 60.0f, 60.0f);

            // 変形前の四角を描画
            render.DrawRectangle(rectangle, originalShapeBrush, 1.0f, stroke);

            // 変形を適用
            var rotation = Matrix.Rotation(45.0f, new PointF(70.0f, 70.0f));
            var translation = Matrix.Translation(20.0f, 10.0f);
            render.SetTransform(translation * rotation);

            // 四角を描画
            render.FillRectangle(rectangle, fillBrush);
            render.DrawRectangle(rectangle, transformedShapeBrush, 1.0f);

            // タイトル描画
            render.SetTransform();
            render.DrawText("Translation then translation", format, new RectangleF(20.0f, 140.0f, 350, 170), textBrush);
        }

        private void RotationTranslation(VisualRenderTarget render,
                                         VisualResourceOfSolidColorBrush originalShapeBrush,
                                         VisualResourceOfSolidColorBrush fillBrush,
                                         VisualResourceOfStrokeStyle stroke,
                                         VisualResourceOfSolidColorBrush transformedShapeBrush,
                                         VisualResourceOfTextFormat format,
                                         VisualResourceOfSolidColorBrush textBrush)
        {
            render.SetTransform();

            // 四角を作成
            var rectangle = new RectangleF(300.0f, 40.0f, 60.0f, 60.0f);

            // 変形前の四角を描画
            render.DrawRectangle(rectangle, originalShapeBrush, 1.0f, stroke);

            // 変形を適用
            var rotation = Matrix.Rotation(45.0f, new PointF(330.0f, 70.0f));
            var translation = Matrix.Translation(20.0f, 10.0f);
            render.SetTransform(rotation * translation);

            // 四角を描画
            render.FillRectangle(rectangle, fillBrush);
            render.DrawRectangle(rectangle, transformedShapeBrush, 1.0f);

            // タイトル描画
            render.SetTransform();
            render.DrawText("Rotation then translation", format, new RectangleF(260.0f, 140.0f, 350, 170), textBrush);
        }
    }
}