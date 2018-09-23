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
            this.Resources.CreateSolidColorBrush("black", Color.Black);

            using (var bmp = new Bitmap("..\\..\\fish.png")) {
                var bit = this.Resources.CreateBitmap("fish bitmap", bmp);

                var original = this.Resources.CreateBitmapBrush("original", bit);
                original.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                original.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                original.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }

            using (var bmp = new Bitmap("..\\..\\mask.png")) {
                var bit = this.Resources.CreateBitmap("mask bitmap", bmp);

                var mask = this.Resources.CreateBitmapBrush("mask", (Bitmap)bmp.Clone());
                mask.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                mask.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                mask.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            var rcBrushRect = new RectangleF(0, 0, 205, 141);

            // 背景色塗り潰し
            e.RenderTarget.Clear(Color.White);

            // オリジナルビットマップ
            e.RenderTarget.SetTransform(5, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["original"]);

            // マスクビットマップ
            e.RenderTarget.SetTransform(255, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["mask"]);

            // 重ね合わせ
            e.RenderTarget.SetTransform(500, 5);
            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_ALIASED);

            e.RenderTarget.FillOpacityMask(e.Resources["mask bitmap"],
                                           e.Resources["original"],
                                           OpacityMaskContent.OPACITY_MASK_CONTENT_GRAPHICS,
                                           rcBrushRect);

            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_PER_PRIMITIVE);
        }
    }
}
