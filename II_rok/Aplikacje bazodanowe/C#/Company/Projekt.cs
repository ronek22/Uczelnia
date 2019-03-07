using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Company
{
    public partial class Projekt : Form
    {

        int clickAdd = 0;
        int clickEdit = 0;
        public Projekt()
        {
            InitializeComponent();
            FormEnabled(false);
        }

        private void Projekt_Load(object sender, EventArgs e)
        {
            try
            {
                this.projektTableAdapter.Fill(this.dataSet_baza.projekt);
            }
            catch (SqlException)
            {
                MessageBox.Show("Brak połączenia z internetem!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            dataGridView1.Columns[5].DefaultCellStyle.Format = "c";

        }

        private void btnInsert_Click(object sender, EventArgs e)
        {
            if (clickAdd % 2 == 0)
            {
                FormEnabled(true);
                // czyszczenie formularza
                btnUsun.Enabled = false;
                btnSave.Enabled = false;
                dataGridView1.Enabled = false;
                clear();
                clickAdd++;
            }
            else
            {
                //Parsowanie
                String vNazw = txtNazwa.Text.Length > 20 ? txtNazwa.Text.Substring(0, 20) : txtNazwa.Text;
                String vOpis = txtOpis.Text.Length > 200 ? txtOpis.Text.Substring(0, 200) : txtOpis.Text;
                decimal budzet = 0;
                decimal.TryParse(txtBudzet.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out budzet);


                Boolean validation = true;

                if (vNazw.Length == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (budzet <= 0)
                {
                    MessageBox.Show("Budzet musi być większy niż 0", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }


                if (dateTimeStart.Value.Date > dateTimeKon.Value.Date)
                {
                    MessageBox.Show("Data staru musi być późniejsza niż data końca", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (validation)
                {
                    FormEnabled(false);
                    try
                    {
                        projektTableAdapter.Insert(vNazw, vOpis, dateTimeStart.Value.Date, dateTimeKon.Value.Date, budzet);

                    }
                    catch (SqlException)
                    {
                        MessageBox.Show("Istnieje już projekt o tej nazwie", "Błąd",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        validation = false;

                    }
                    dataSet_baza.AcceptChanges();
                    projektTableAdapter.Update(dataSet_baza.projekt);
                    this.projektTableAdapter.Fill(this.dataSet_baza.projekt);

                    //wlaczenie przyciskow
                    dataGridView1.Enabled = true;
                    btnUsun.Enabled = true;
                    btnSave.Enabled = true;
                    clickAdd = 0;
                }

            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Boolean validation = true;
            if (clickEdit % 2 == 0)
            {
                FormEnabled(true);
                btnInsert.Enabled = false;
                btnUsun.Enabled = false;
                // dataGridPracownik.Enabled = false;
                clickEdit++;
            }
            else
            {
                dataGridView1.RefreshEdit();

                decimal budzet = 0;
                decimal.TryParse(txtBudzet.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out budzet);


                if (txtNazwa.Text.Length == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (budzet <= 0)
                {
                    MessageBox.Show("Budzet musi być większy niż 0", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dateTimeStart.Value.Date > dateTimeKon.Value.Date)
                {
                    MessageBox.Show("Data staru musi być późniejsza niż data końca", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }
                if (validation)
                {

                    //aktualizuje bazę o wpisy w
                    projektTableAdapter.Update(dataSet_baza.projekt);
                    this.projektTableAdapter.Fill(this.dataSet_baza.projekt);
                    btnInsert.Enabled = true;
                    btnUsun.Enabled = true;
                    dataGridView1.Enabled = true;
                    FormEnabled(false);
                    clickEdit = 0;
                }
            }
        }

        private void btnUsun_Click(object sender, EventArgs e)
        {
            var confirmResult = MessageBox.Show("Jesteś pewny, że chcesz usunąć ten rekord ??",
                       "Potwierdź usuwanie!!",
                       MessageBoxButtons.YesNo);
            if (confirmResult == DialogResult.Yes)
            {
                //sprawdza czy jest zaznaczony wiersz
                if (dataGridView1.CurrentRow != null)
                {
                    dataGridView1.CurrentRow.Selected = true;
                    //usuwa zaznaczony wiersz
                    dataGridView1.Rows.Remove(dataGridView1.SelectedRows[0]);
                    projektTableAdapter.Update(dataSet_baza.projekt);
                    this.projektTableAdapter.Fill(this.dataSet_baza.projekt);
                }
            }
        }

        private void FormEnabled(Boolean enable)
        {
            if (enable)
            {
                txtNazwa.Enabled = true;
                txtOpis.Enabled = true;
                txtBudzet.Enabled = true;
                dateTimeStart.Enabled = true;
                dateTimeKon.Enabled = true;

            }
            else
            {
                txtNazwa.Enabled = false;
                txtOpis.Enabled = false;
                txtBudzet.Enabled = false;
                dateTimeStart.Enabled = false;
                dateTimeKon.Enabled = false;
            }

        }
        private void clear()
        {
            txtNazwa.Text = String.Empty;
            txtOpis.Text = String.Empty;
            txtBudzet.Text = String.Empty;
            dateTimeStart.Text = String.Empty;
            dateTimeKon.Text = String.Empty;
        }
    }
}
