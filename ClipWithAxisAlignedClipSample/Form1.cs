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
            // ビットマップ
            using (var bmp = new Bitmap("..\\..\\fish.png")) {
                this.Resources.CreateBitmapBrush("bitmap", bmp);
            }
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            // 背景色を塗りつぶす
            e.RenderTarget.Clear(Color.White);

            var rcBrushRect = new RectangleF(0, 0, 378, 284);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);

            e.RenderTarget.SetTransform(420, 0);
            e.RenderTarget.PushAxisAlignedClip(new RectangleF(100, 20, 100, 100), AntialiasMode.ANTIALIAS_MODE_PER_PRIMITIVE);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.PopAxisAlignedClip();
        }
    }
}
