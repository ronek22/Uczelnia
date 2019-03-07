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
    public partial class Stanowisko : Form
    {

        int clickAdd = 0;
        int clickEdit = 0;
        public Stanowisko()
        {
            InitializeComponent();
            FormEnabled(false);
        }

        private void Stanowisko_Load(object sender, EventArgs e)
        {
            try
            {
                this.stanowiskoTableAdapter.Fill(this.dataSet_baza.stanowisko);
            }
            catch (SqlException)
            {
                MessageBox.Show("Brak połączenia z internetem!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            dataGridViewStanowisko.Columns[3].DefaultCellStyle.Format = "c";
            dataGridViewStanowisko.Columns[4].DefaultCellStyle.Format = "c";
        }

        private void btnInsert_Click(object sender, EventArgs e)
        {
            if (clickAdd % 2 == 0)
            {
                FormEnabled(true);
                // czyszczenie formularza
                btnUsun.Enabled = false;
                btnSave.Enabled = false;
                dataGridViewStanowisko.Enabled = false;
                clear();
                clickAdd++;
            }
            else
            {
                //Parsowanie
                String vNazw = txtNazwa.Text.Length > 20 ? txtNazwa.Text.Substring(0, 20) : txtNazwa.Text;
                String vOpis = txtOpis.Text.Length > 100 ? txtOpis.Text.Substring(0, 100) : txtOpis.Text;
                decimal dolna = 0;
                decimal gorna = 0;
                decimal.TryParse(txtDolna.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out dolna);
                decimal.TryParse(txtGorna.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out gorna);


                Boolean validation = true;

                if (vNazw.Length == 0 || dolna == 0 || gorna == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dolna > gorna)
                {
                    MessageBox.Show("Górna granica pensji nie może być mniejsza niż dolna", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (validation)
                {
                    FormEnabled(false);
                    FormEnabled(false);
                    try
                    {
                        stanowiskoTableAdapter.Insert(vNazw, vOpis, dolna, gorna, dateTimeDod.Value.Date);
                   
                    }
                    catch (SqlException)
                    {
                        MessageBox.Show("Istnieje już stanowisko o tej nazwie", "Błąd",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        validation = false;

                    }
                    
                    dataSet_baza.AcceptChanges();
                    stanowiskoTableAdapter.Update(dataSet_baza.stanowisko);
                    this.stanowiskoTableAdapter.Fill(this.dataSet_baza.stanowisko);

                    //wlaczenie przyciskow
                    dataGridViewStanowisko.Enabled = true;
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
                dataGridViewStanowisko.RefreshEdit();

                decimal dolna = 0;
                decimal gorna = 0;
                decimal.TryParse(txtDolna.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out dolna);
                decimal.TryParse(txtGorna.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out gorna);

                if (txtNazwa.Text.Length == 0 || txtDolna.Text.Length == 0 || txtGorna.Text.Equals("0"))
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dolna > gorna)
                {
                    MessageBox.Show("Górna granica pensji nie może być mniejsza niż dolna", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }
                if (validation)
                {

                    //aktualizuje bazę o wpisy w
                    stanowiskoTableAdapter.Update(dataSet_baza.stanowisko);
                    this.stanowiskoTableAdapter.Fill(this.dataSet_baza.stanowisko);
                    btnInsert.Enabled = true;
                    btnUsun.Enabled = true;
                    dataGridViewStanowisko.Enabled = true;
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
                if (dataGridViewStanowisko.CurrentRow != null)
                {
                    dataGridViewStanowisko.CurrentRow.Selected = true;
                    //usuwa zaznaczony wiersz
                    dataGridViewStanowisko.Rows.Remove(dataGridViewStanowisko.SelectedRows[0]);
                    stanowiskoTableAdapter.Update(dataSet_baza.stanowisko);
                    this.stanowiskoTableAdapter.Fill(this.dataSet_baza.stanowisko);
                }
            }
        }


        private void FormEnabled(Boolean enable)
        {
            if (enable)
            {
                txtNazwa.Enabled = true;
                txtOpis.Enabled = true;
                txtDolna.Enabled = true;
                txtGorna.Enabled = true;
                dateTimeDod.Enabled = true;

            }
            else
            {
                txtNazwa.Enabled = false;
                txtOpis.Enabled = false;
                txtDolna.Enabled = false;
                txtGorna.Enabled = false;
                dateTimeDod.Enabled = false;
            }

        }
        private void clear()
        {
            txtNazwa.Text = String.Empty;
            txtOpis.Text = String.Empty;
            dateTimeDod.Text = String.Empty;
            txtDolna.Text = String.Empty;
            txtGorna.Text = String.Empty;
        }


    }
}
