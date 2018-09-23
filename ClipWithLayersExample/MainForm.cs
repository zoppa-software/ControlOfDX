using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DrawRectangleExample
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var f = new Form1();
            f.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var f = new Form2();
            f.Show();
        }
    }
}
