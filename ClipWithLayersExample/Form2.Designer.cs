namespace DrawRectangleExample
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainControl = new ControlOfDX.VisualControl();
            this.SuspendLayout();
            // 
            // mainControl
            // 
            this.mainControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainControl.Location = new System.Drawing.Point(0, 0);
            this.mainControl.Name = "mainControl";
            this.mainControl.Size = new System.Drawing.Size(1079, 450);
            this.mainControl.TabIndex = 0;
            this.mainControl.Rendering += new ControlOfDX.VisualControl.VisualRenderEventHandler(this.mainlControl_Rendering);
            this.mainControl.InitializeResource += new System.EventHandler(this.mainlControl_InitializeResource);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1079, 450);
            this.Controls.Add(this.mainControl);
            this.Name = "Form2";
            this.Text = "Form3";
            this.ResumeLayout(false);

        }

        #endregion

        private ControlOfDX.VisualControl mainControl;
    }
}