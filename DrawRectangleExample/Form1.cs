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
            this.Resources.CreateSolidColorBrush("LightSlateGrayBrush", Color.LightSlateGray);
            this.Resources.CreateSolidColorBrush("CornflowerBlueBrush", Color.CornflowerBlue);
        }

        protected override void OnRendering(VisualRenderEventArgs e)
        {
            e.RenderTarget.SetTransform();

            e.RenderTarget.Clear(Color.White);

            for (int x = 0; x < this.ClientSize.Width; x += 10) {
                e.RenderTarget.DrawLine(new PointF(x, 0),
                                        new PointF(x, this.ClientSize.Height),
                                        e.Resources["LightSlateGrayBrush"], 0.5f);
            }

            for (int y = 0; y < this.ClientSize.Height; y += 10) {
                e.RenderTarget.DrawLine(new PointF(0, y),
                                        new PointF(this.ClientSize.Width, y),
                                        e.Resources["LightSlateGrayBrush"], 0.5f);
            }

            var rectangle1 = new RectangleF(
                this.ClientSize.Width / 2 - 50.0f,
                this.ClientSize.Height / 2 - 50.0f,
                100.0f,
                100.0f
            );
            var rectangle2 = new RectangleF(
                this.ClientSize.Width / 2 - 100.0f,
                this.ClientSize.Height / 2 - 100.0f,
                200.0f,
                200.0f
            );

            e.RenderTarget.FillRectangle(rectangle1, e.Resources["LightSlateGrayBrush"]);

            e.RenderTarget.DrawRectangle(rectangle1, e.Resources["CornflowerBlueBrush"], 1.0f);
        }
    }
}
