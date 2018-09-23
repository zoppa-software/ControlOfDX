using System;
using System.Drawing;
using ControlOfDX;

namespace DrawRectangleExample
{
    public partial class Form1
        : ControlOfDX.VisualForm
    {
        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnInitializeResource(EventArgs e)
        {
            // 黒ブラシ
            this.Resources.CreateSolidColorBrush("brush", Color.Black);

            // 画像ブラシ
            using (var bmp = new Bitmap("..\\..\\leaf_sample.jpg")) {
                this.Resources.CreateBitmapBrush("bitmap", bmp);
            }
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            var rcBrushRect = new RectangleF(5, 5, 150, 150);
            var rcTransformedBrushRect = new RectangleF(100, 100, 100, 100);

            // 背景塗りつぶし
            e.RenderTarget.Clear(Color.White);

            // オリジナル画像
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["brush"], 1);

            // 部分描画
            e.RenderTarget.FillRectangle(rcTransformedBrushRect, e.Resources["bitmap"]);

            // 部分を移動して描画
            var brush = (VisualResourceOfBitmapBrush)e.Resources["bitmap"];
            brush.SetTransform(Matrix.Translation(50, 50));
            e.RenderTarget.FillRectangle(rcTransformedBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.DrawRectangle(rcTransformedBrushRect, e.Resources["brush"], 1);
        }
    }
}
