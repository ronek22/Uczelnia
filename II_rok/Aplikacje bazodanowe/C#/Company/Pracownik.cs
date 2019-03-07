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
    public partial class Pracownik : Form
    {
        int clickAdd = 0;
        int clickEdit = 0;

        public Pracownik()
        {
            InitializeComponent();
            FormEnabled(false);

        }


        private void Pracownik_Load(object sender, EventArgs e)
        {
            try
            {
                this.stanowiskoTableAdapter.Fill(this.dataSet_baza.stanowisko);
                this.pracownikTableAdapter.Fill(this.dataSet_baza.pracownik);
            }
            catch (SqlException)
            {
                MessageBox.Show("Brak połączenia z internetem!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        
            dataGridPracownik.Columns[6].DefaultCellStyle.Format = "c";

        }

        private void btnUsun_Click(object sender, EventArgs e)
        {
            var confirmResult = MessageBox.Show("Jesteś pewny, że chcesz usunąć ten rekord ??",
                                     "Potwierdź usuwanie!!",
                                     MessageBoxButtons.YesNo);
            if (confirmResult == DialogResult.Yes)
            {
                //sprawdza czy jest zaznaczony wiersz
                if (dataGridPracownik.CurrentRow != null)
                {
                    dataGridPracownik.CurrentRow.Selected = true;
                    //usuwa zaznaczony wiersz
                    dataGridPracownik.Rows.Remove(dataGridPracownik.SelectedRows[0]);
                    pracownikTableAdapter.Update(dataSet_baza.pracownik);
                    this.pracownikTableAdapter.Fill(this.dataSet_baza.pracownik);
                }
            }

        }

        private void btnZapisz_Click(object sender, EventArgs e)
        {
            Boolean validation = true;
            if(clickEdit % 2 == 0)
            {
                FormEnabled(true);
                btnInsert.Enabled = false;
                btnUsun.Enabled = false;
               // dataGridPracownik.Enabled = false;
                clickEdit++;
            } else
            {
                dataGridPracownik.RefreshEdit();
                if (txtImie.Text.Length == 0 || txtNazwisko.Text.Length == 0 || txtPensja.Text.Equals("0"))
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (dateTimeUr.Value.Date > dateTimeZat.Value.Date)
                {
                    MessageBox.Show("Data zatrudnienia musi być późniejsza niż data urodzenia", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }
                if (validation)
                {

                    //aktualizuje bazę o wpisy w
                    pracownikTableAdapter.Update(dataSet_baza.pracownik);
                    this.pracownikTableAdapter.Fill(this.dataSet_baza.pracownik);
                    btnInsert.Enabled = true;
                    btnUsun.Enabled = true;
                    dataGridPracownik.Enabled = true;
                    FormEnabled(false);
                    clickEdit = 0;
                }
            }

          


        }

        private void Pracownik_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult dr = MessageBox.Show("Czy chcesz zapisać wszystkie zmiany, które wprowadziłeś?",
            "UWAGA!!!", MessageBoxButtons.YesNo);
            if (dr == DialogResult.Yes)
            {
                pracownikTableAdapter.Update(dataSet_baza.pracownik);
            }
        }

        private void btnInsert_Click(object sender, EventArgs e)
        {

            if (clickAdd % 2 == 0)
            {
                FormEnabled(true);
                // czyszczenie formularza
                btnUsun.Enabled = false;
                btnZapisz.Enabled = false;
                dataGridPracownik.Enabled = false;
                clear();
                clickAdd++;

            }
            else
            {
                //Parsowanie
                String vImie = txtImie.Text.Length > 20 ? txtImie.Text.Substring(0, 20) : txtImie.Text;
                String vNazw = txtNazwisko.Text.Length > 20 ? txtNazwisko.Text.Substring(0, 20) : txtNazwisko.Text;
                int idStan = 0;
                decimal Salary = 0;
                decimal.TryParse(txtPensja.Text, NumberStyles.Currency, CultureInfo.CurrentCulture.NumberFormat, out Salary);
                int.TryParse(cmbStan.SelectedValue.ToString(), out idStan);


                Boolean validation = true;
                
                if(vImie.Length == 0 || vNazw.Length == 0 || Salary == 0)
                {
                    MessageBox.Show("Uzupełnij wszystkie pola", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;
                   
                }

                if(dateTimeUr.Value.Date > dateTimeZat.Value.Date)
                {
                    MessageBox.Show("Data zatrudnienia musi być późniejsza niż data urodzenia", "Błąd",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    validation = false;

                }

                if (validation)
                {
                    FormEnabled(false);
                    try
                    {
                        pracownikTableAdapter.Insert(idStan, vImie, vNazw, dateTimeUr.Value.Date, dateTimeZat.Value.Date, Salary);

                    }
                    catch (SqlException)
                    {
                        MessageBox.Show("Istnieje już pracownik o tym imieniu i nazwisku", "Błąd",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        validation = false;

                    }
                    dataSet_baza.AcceptChanges();
                    pracownikTableAdapter.Update(dataSet_baza.pracownik);
                    this.pracownikTableAdapter.Fill(this.dataSet_baza.pracownik);

                    //wlaczenie przyciskow
                    dataGridPracownik.Enabled = true;
                    btnUsun.Enabled = true;
                    btnZapisz.Enabled = true;
                    clickAdd = 0;
                }

            }

        }

        private void FormEnabled(Boolean enable)
        {
            if (enable)
            {
                txtImie.Enabled = true;
                txtNazwisko.Enabled = true;
                dateTimeUr.Enabled = true;
                dateTimeZat.Enabled = true;
                txtPensja.Enabled = true;
                cmbStan.Enabled = true;
            } else
            {
                txtImie.Enabled = false;
                txtNazwisko.Enabled = false;
                dateTimeUr.Enabled = false;
                dateTimeZat.Enabled = false;
                txtPensja.Enabled = false;
                cmbStan.Enabled = false;
            }

        }
        private void clear()
        {
            txtImie.Text = String.Empty;
            txtNazwisko.Text = String.Empty;
            dateTimeUr.Text = String.Empty;
            dateTimeZat.Text = String.Empty;
            txtPensja.Text = String.Empty;
        }
    }
}
