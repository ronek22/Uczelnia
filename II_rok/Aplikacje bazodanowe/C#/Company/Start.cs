using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Company
{
    public partial class Start : Form
    {
        public Start()
        {
            InitializeComponent();
        }


        private void stanowiskoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Stanowisko stanowisko = new Stanowisko();
            stanowisko.MdiParent = this;
            stanowisko.Show();
        }

        private void pracownikToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Pracownik pracownik = new Pracownik();
            pracownik.MdiParent = this;
            pracownik.Show();
        }

        private void projektToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Projekt projekt = new Projekt();
            projekt.MdiParent = this;
            projekt.Show();
        }

        private void zadaniaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Zadania zadania = new Zadania();
            zadania.MdiParent = this;
            zadania.Show();
        }


    }
}
