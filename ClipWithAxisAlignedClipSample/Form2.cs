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
            // ビットマップ
            using (var bmp = new Bitmap("..\\..\\fish.png")) {
                this.mainControl.Resources.CreateBitmapBrush("bitmap", bmp);
            }
        }

        private void mainlControl_Rendering(object sender, ControlOfDX.VisualRenderEventArgs e)
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