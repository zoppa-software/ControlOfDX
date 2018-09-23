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
            // フォント設定
            var format = this.Resources.CreateTextFormat("format");
            format.FontFamilyName = "Verdana";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_NORMAL;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontStretch = DWriteFontStretch.DWRITE_FONT_STRETCH_NORMAL;
            format.FontSize = 10.0f;

            // 黒ブラシ
            this.Resources.CreateSolidColorBrush("black brush", Color.Black);

            // ビットマップ
            using (var bmp = new Bitmap("..\\..\\Triangle.png")) {
                var bit = this.Resources.CreateBitmap("Triangle", bmp);

                var brh = this.Resources.CreateBitmapBrush("BitmapBrush", bit);
                brh.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                brh.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                brh.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);

            var exampleRectangle = new RectangleF(0, 0, 88, 88);
            var captionBounds = new RectangleF(0, 90, 100, 35);

            var brush = (VisualResourceOfD2BitmapBrush)e.Resources["BitmapBrush"];

            // 1
            e.RenderTarget.SetTransform(5, 5);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("CLAMP for X\nCLAMP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 2
            e.RenderTarget.SetTransform(115, 5);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_WRAP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("CLAMP for X\nWRAP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 3
            e.RenderTarget.SetTransform(225, 5);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_MIRROR;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("CLAMP for X\nMIRROR for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 4
            e.RenderTarget.SetTransform(5, 155);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_WRAP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("WRAP for X\nCLAMP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 5
            e.RenderTarget.SetTransform(115, 155);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_WRAP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_WRAP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("WRAP for X\nWRAP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 6
            e.RenderTarget.SetTransform(225, 155);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_WRAP;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_MIRROR;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("WRAP for X\nMIRROR for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 7
            e.RenderTarget.SetTransform(5, 305);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_MIRROR;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("MIRROR for X\nCLAMP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 8
            e.RenderTarget.SetTransform(115, 305);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_MIRROR;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_WRAP;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("MIRROR for X\nWRAP for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);

            // 9
            e.RenderTarget.SetTransform(225, 305);
            brush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_MIRROR;
            brush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_MIRROR;
            e.RenderTarget.FillRectangle(exampleRectangle, brush);
            e.RenderTarget.DrawRectangle(exampleRectangle, e.Resources["black brush"], 1);
            e.RenderTarget.DrawText("MIRROR for X\nMIRROR for Y", e.Resources["format"], captionBounds, e.Resources["black brush"]);
        }
    }
}
