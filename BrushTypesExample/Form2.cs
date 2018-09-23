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
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_BOLD;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontSize = 10.5f;

            // 黒ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("brush", Color.Black);

            // 薄黄ブラシ
            this.mainControl.Resources.CreateSolidColorBrush("yellow brush", Color.FromArgb(104, 0x9a, 0xcd, 0x32));

            // ライングラデーション
            var line = this.mainControl.Resources.CreateLinearGradientBrush("line");
            line.AddGradientStop(Color.Yellow, 0);
            line.AddGradientStop(Color.ForestGreen, 0.5f);
            line.AddGradientStop(Color.BurlyWood, 1);
            line.Propertes.StartPoint = new PointF(0, 0);
            line.Propertes.EndPoint = new PointF(150, 150);

            // 放射グラデーション
            var radial = this.mainControl.Resources.CreateRadialGradientBrush("radial");
            radial.AddGradientStop(Color.Yellow, 0);
            radial.AddGradientStop(Color.ForestGreen, 0.5f);
            radial.AddGradientStop(Color.BurlyWood, 1);
            radial.Propertes.Center = new PointF(75, 75);
            radial.Propertes.GradientOriginOffset = new PointF(30, -30);
            radial.Propertes.RadiusX = 75;
            radial.Propertes.RadiusY = 75;

            // ビットマップ
            using (var bmp = new Bitmap("..\\..\\fern.jpg")) {
                this.mainControl.Resources.CreateBitmapBrush("bitmap", (Bitmap)bmp.Clone());
            }
        }

        private void mainlControl_Rendering(object sender, ControlOfDX.VisualRenderEventArgs e)
        {
            // ブラシで塗りつぶす矩形の形状を定義する
            var rcBrushRect = new RectangleF(5, 0, 150, 150);

            // キャプションが描画される領域を定義する
            var rcTextRect = new RectangleF(5, 165, 175, 200);

            // 背景色を塗りつぶす
            e.RenderTarget.Clear(Color.White);

            // 単色ブラシ
            e.RenderTarget.SetTransform(5, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["yellow brush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["brush"], 1);
            e.RenderTarget.DrawText("ID2D1SolidColorBrush", e.Resources["text format"], rcTextRect, e.Resources["brush"]);

            // ライングラデーションブラシ
            e.RenderTarget.SetTransform(200, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["line"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["brush"], 1);
            e.RenderTarget.DrawText("ID2D1LinearGradientBrush", e.Resources["text format"], rcTextRect, e.Resources["brush"]);

            // 放射グラデーションブラシ
            e.RenderTarget.SetTransform();
            e.RenderTarget.SetTransform(5, 200);

            var ellipse = new Ellipse(new PointF(75.0f, 75.0f), 75.0f, 75.0f);
            e.RenderTarget.FillEllipse(ellipse, e.Resources["radial"]);
            e.RenderTarget.DrawEllipse(ellipse, e.Resources["brush"], 1);
            e.RenderTarget.DrawText("ID2D1RadialGradientBrush", e.Resources["text format"], rcTextRect, e.Resources["brush"]);

            // ビットマップブラシ
            e.RenderTarget.SetTransform(200, 200);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["brush"], 1);
            e.RenderTarget.DrawText("ID2D1BitmapBrush", e.Resources["text format"], rcTextRect, e.Resources["brush"]);
        }
    }
}