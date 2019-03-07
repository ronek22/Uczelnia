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
    public partial class Zadania : Form
    {

        int clickAdd = 0;
        int clickEdit = 0;

        public Zadania()
        {
            InitializeComponent();
            FormEnabled(false);
        }

        private void Zadania_Load(object sender, EventArgs e)
        {
            try
            {
                this.projektTableAdapter.Fill(this.dataSet_baza.projekt);
                this.pracownikTableAdapter.Fill(this.dataSet_baza.pracownik);
                this.zadania_pracownikowTableAdapter.Fill(this.dataSet_baza.zadania_pracownikow);
            }
            catch (SqlException)
            {
                MessageBox.Show("Brak połączenia z internetem!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            dataGridViewZadania.Columns[2].DefaultCellStyle.Format = "c";
        }

        private void btnInsert_Click(object sender, EventArgs e)
        {
            if (clickAdd % 2 == 0)
            {
                FormEnabled(true);
                // czyszczenie formularza
                btnUsun.Enabled = false;
                btnSave.Enabled = false;
                dataGridViewZadania.Enabled = false;
                clear();
                clickAdd++;

            }
            else
            {
                //Parsowanie
                String vKom = txtKom.Text.Length > 200 ? txtKom.Text.Substring(0, 200) : txtKom.Text;
                int idPrac = 0;
                int idProj = 0;
                decimal stawka = 0;
                int godziny = Convert.ToInt32(numGodziny.Value);


                decimal.TryParse(txtStawka.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out stawka);
                int.TryParse(cmbPrac.SelectedValue.ToString(), out idPrac);
                int.TryParse(cmbProjekt.SelectedValue.ToString(), out idProj);


                Boolean validation = true;

                if (stawka == 0 || godziny == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dateTimeStart.Value.Date > dateTimeKon.Value.Date)
                {
                    MessageBox.Show("Data startu musi być późniejsza niż data konca", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (validation)
                {
                    FormEnabled(false);
                    try
                    {
                        zadania_pracownikowTableAdapter.Insert(idProj, idPrac, stawka, godziny, vKom, dateTimeStart.Value.Date, dateTimeKon.Value.Date);
                    }
                    catch(SqlException)
                    {
                        MessageBox.Show("Prawdopodbnie ten pracownik już ma przypisany ten projekt", "Błąd",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        validation = false;
                        
                    }
                    
                    dataSet_baza.AcceptChanges();
                    zadania_pracownikowTableAdapter.Update(dataSet_baza.zadania_pracownikow);
                    this.zadania_pracownikowTableAdapter.Fill(this.dataSet_baza.zadania_pracownikow);

                    //wlaczenie przyciskow
                    dataGridViewZadania.Enabled = true;
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
                clickEdit++;
            }
            else
            {
                dataGridViewZadania.RefreshEdit();
                if (txtStawka.Text.Length == 0 || numGodziny.Value == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dateTimeStart.Value.Date > dateTimeKon.Value.Date)
                {
                    MessageBox.Show("Data startu musi być późniejsza niż data konca", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (validation)
                {

                    //aktualizuje bazę o wpisy w
                    zadania_pracownikowTableAdapter.Update(dataSet_baza.zadania_pracownikow);
                    this.zadania_pracownikowTableAdapter.Fill(this.dataSet_baza.zadania_pracownikow);
                    btnInsert.Enabled = true;
                    btnUsun.Enabled = true;
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
                if (dataGridViewZadania.CurrentRow != null)
                {
                    dataGridViewZadania.CurrentRow.Selected = true;
                    //usuwa zaznaczony wiersz
                    dataGridViewZadania.Rows.Remove(dataGridViewZadania.SelectedRows[0]);
                    zadania_pracownikowTableAdapter.Update(dataSet_baza.zadania_pracownikow);
                    this.zadania_pracownikowTableAdapter.Fill(this.dataSet_baza.zadania_pracownikow);
                }
            }
        }

        private void FormEnabled(Boolean enable)
        {
            if (enable)
            {
                cmbProjekt.Enabled = true;
                cmbPrac.Enabled = true;
                txtStawka.Enabled = true;
                numGodziny.Enabled = true;
                txtKom.Enabled = true;
                dateTimeStart.Enabled = true;
                dateTimeKon.Enabled = true;
            }
            else
            {
                cmbProjekt.Enabled = false;
                cmbPrac.Enabled = false;
                txtStawka.Enabled = false;
                numGodziny.Enabled = false;
                txtKom.Enabled = false;
                dateTimeStart.Enabled = false;
                dateTimeKon.Enabled = false;
            }

        }
        private void clear()
        {


            txtStawka.Text = String.Empty;
            numGodziny.Text = String.Empty;
            txtKom.Text = String.Empty;
            dateTimeStart.Text = String.Empty;
            dateTimeKon.Text = String.Empty;
        }
    }
}
