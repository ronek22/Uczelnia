namespace Company
{
    partial class Pracownik
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
            if (disposing && (components != null))
            {
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
            this.components = new System.ComponentModel.Container();
            this.dataGridPracownik = new System.Windows.Forms.DataGridView();
            this.idpracownikDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.idstanowiskoDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.stanowiskoBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.dataSet_baza = new Company.DataSet_baza();
            this.imieDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nazwiskoDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataurodzeniaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datazatrudnieniaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pensjaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.pracownikBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.pracownikTableAdapter = new Company.DataSet_bazaTableAdapters.pracownikTableAdapter();
            this.stanowiskoTableAdapter = new Company.DataSet_bazaTableAdapters.stanowiskoTableAdapter();
            this.btnZapisz = new System.Windows.Forms.Button();
            this.btnUsun = new System.Windows.Forms.Button();
            this.txtImie = new System.Windows.Forms.TextBox();
            this.txtNazwisko = new System.Windows.Forms.TextBox();
            this.dateTimeUr = new System.Windows.Forms.DateTimePicker();
            this.dateTimeZat = new System.Windows.Forms.DateTimePicker();
            this.txtPensja = new System.Windows.Forms.TextBox();
            this.cmbStan = new System.Windows.Forms.ComboBox();
            this.stanowiskoBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.dataSetbazaBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.lStanowisko = new System.Windows.Forms.Label();
            this.lImie = new System.Windows.Forms.Label();
            this.lNazwisko = new System.Windows.Forms.Label();
            this.lDataUr = new System.Windows.Forms.Label();
            this.lDataZat = new System.Windows.Forms.Label();
            this.lPensja = new System.Windows.Forms.Label();
            this.btnInsert = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridPracownik)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetbazaBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridPracownik
            // 
            this.dataGridPracownik.AllowUserToAddRows = false;
            this.dataGridPracownik.AutoGenerateColumns = false;
            this.dataGridPracownik.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridPracownik.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridPracownik.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idpracownikDataGridViewTextBoxColumn,
            this.idstanowiskoDataGridViewTextBoxColumn,
            this.imieDataGridViewTextBoxColumn,
            this.nazwiskoDataGridViewTextBoxColumn,
            this.dataurodzeniaDataGridViewTextBoxColumn,
            this.datazatrudnieniaDataGridViewTextBoxColumn,
            this.pensjaDataGridViewTextBoxColumn});
            this.dataGridPracownik.DataSource = this.pracownikBindingSource;
            this.dataGridPracownik.Location = new System.Drawing.Point(12, 12);
            this.dataGridPracownik.Name = "dataGridPracownik";
            this.dataGridPracownik.Size = new System.Drawing.Size(618, 306);
            this.dataGridPracownik.TabIndex = 0;
            // 
            // idpracownikDataGridViewTextBoxColumn
            // 
            this.idpracownikDataGridViewTextBoxColumn.DataPropertyName = "id_pracownik";
            this.idpracownikDataGridViewTextBoxColumn.HeaderText = "id_pracownik";
            this.idpracownikDataGridViewTextBoxColumn.Name = "idpracownikDataGridViewTextBoxColumn";
            this.idpracownikDataGridViewTextBoxColumn.ReadOnly = true;
            this.idpracownikDataGridViewTextBoxColumn.Visible = false;
            // 
            // idstanowiskoDataGridViewTextBoxColumn
            // 
            this.idstanowiskoDataGridViewTextBoxColumn.DataPropertyName = "id_stanowisko";
            this.idstanowiskoDataGridViewTextBoxColumn.DataSource = this.stanowiskoBindingSource;
            this.idstanowiskoDataGridViewTextBoxColumn.DisplayMember = "nazwa";
            this.idstanowiskoDataGridViewTextBoxColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.Nothing;
            this.idstanowiskoDataGridViewTextBoxColumn.HeaderText = "stanowisko";
            this.idstanowiskoDataGridViewTextBoxColumn.Name = "idstanowiskoDataGridViewTextBoxColumn";
            this.idstanowiskoDataGridViewTextBoxColumn.ReadOnly = true;
            this.idstanowiskoDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.idstanowiskoDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.idstanowiskoDataGridViewTextBoxColumn.ValueMember = "id_stanowisko";
            // 
            // stanowiskoBindingSource
            // 
            this.stanowiskoBindingSource.DataMember = "stanowisko";
            this.stanowiskoBindingSource.DataSource = this.dataSet_baza;
            // 
            // dataSet_baza
            // 
            this.dataSet_baza.DataSetName = "DataSet_baza";
            this.dataSet_baza.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // imieDataGridViewTextBoxColumn
            // 
            this.imieDataGridViewTextBoxColumn.DataPropertyName = "imie";
            this.imieDataGridViewTextBoxColumn.HeaderText = "imie";
            this.imieDataGridViewTextBoxColumn.Name = "imieDataGridViewTextBoxColumn";
            // 
            // nazwiskoDataGridViewTextBoxColumn
            // 
            this.nazwiskoDataGridViewTextBoxColumn.DataPropertyName = "nazwisko";
            this.nazwiskoDataGridViewTextBoxColumn.HeaderText = "nazwisko";
            this.nazwiskoDataGridViewTextBoxColumn.Name = "nazwiskoDataGridViewTextBoxColumn";
            // 
            // dataurodzeniaDataGridViewTextBoxColumn
            // 
            this.dataurodzeniaDataGridViewTextBoxColumn.DataPropertyName = "data_urodzenia";
            this.dataurodzeniaDataGridViewTextBoxColumn.HeaderText = "data_urodzenia";
            this.dataurodzeniaDataGridViewTextBoxColumn.Name = "dataurodzeniaDataGridViewTextBoxColumn";
            // 
            // datazatrudnieniaDataGridViewTextBoxColumn
            // 
            this.datazatrudnieniaDataGridViewTextBoxColumn.DataPropertyName = "data_zatrudnienia";
            this.datazatrudnieniaDataGridViewTextBoxColumn.HeaderText = "data_zatrudnienia";
            this.datazatrudnieniaDataGridViewTextBoxColumn.Name = "datazatrudnieniaDataGridViewTextBoxColumn";
            // 
            // pensjaDataGridViewTextBoxColumn
            // 
            this.pensjaDataGridViewTextBoxColumn.DataPropertyName = "pensja";
            this.pensjaDataGridViewTextBoxColumn.HeaderText = "pensja";
            this.pensjaDataGridViewTextBoxColumn.Name = "pensjaDataGridViewTextBoxColumn";
            // 
            // pracownikBindingSource
            // 
            this.pracownikBindingSource.DataMember = "pracownik";
            this.pracownikBindingSource.DataSource = this.dataSet_baza;
            // 
            // pracownikTableAdapter
            // 
            this.pracownikTableAdapter.ClearBeforeFill = true;
            // 
            // stanowiskoTableAdapter
            // 
            this.stanowiskoTableAdapter.ClearBeforeFill = true;
            // 
            // btnZapisz
            // 
            this.btnZapisz.Location = new System.Drawing.Point(727, 270);
            this.btnZapisz.Name = "btnZapisz";
            this.btnZapisz.Size = new System.Drawing.Size(75, 23);
            this.btnZapisz.TabIndex = 1;
            this.btnZapisz.Text = "Edytuj";
            this.btnZapisz.UseVisualStyleBackColor = true;
            this.btnZapisz.Click += new System.EventHandler(this.btnZapisz_Click);
            // 
            // btnUsun
            // 
            this.btnUsun.Location = new System.Drawing.Point(808, 270);
            this.btnUsun.Name = "btnUsun";
            this.btnUsun.Size = new System.Drawing.Size(75, 23);
            this.btnUsun.TabIndex = 2;
            this.btnUsun.Text = "Usuń";
            this.btnUsun.UseVisualStyleBackColor = true;
            this.btnUsun.Click += new System.EventHandler(this.btnUsun_Click);
            // 
            // txtImie
            // 
            this.txtImie.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.pracownikBindingSource, "imie", true));
            this.txtImie.Location = new System.Drawing.Point(709, 14);
            this.txtImie.MaxLength = 20;
            this.txtImie.Name = "txtImie";
            this.txtImie.Size = new System.Drawing.Size(159, 20);
            this.txtImie.TabIndex = 3;
            // 
            // txtNazwisko
            // 
            this.txtNazwisko.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.pracownikBindingSource, "nazwisko", true));
            this.txtNazwisko.Location = new System.Drawing.Point(709, 41);
            this.txtNazwisko.MaxLength = 20;
            this.txtNazwisko.Name = "txtNazwisko";
            this.txtNazwisko.Size = new System.Drawing.Size(159, 20);
            this.txtNazwisko.TabIndex = 4;
            // 
            // dateTimeUr
            // 
            this.dateTimeUr.CustomFormat = "";
            this.dateTimeUr.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.pracownikBindingSource, "data_urodzenia", true));
            this.dateTimeUr.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeUr.Location = new System.Drawing.Point(709, 67);
            this.dateTimeUr.Name = "dateTimeUr";
            this.dateTimeUr.Size = new System.Drawing.Size(159, 20);
            this.dateTimeUr.TabIndex = 5;
            // 
            // dateTimeZat
            // 
            this.dateTimeZat.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.pracownikBindingSource, "data_zatrudnienia", true));
            this.dateTimeZat.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeZat.Location = new System.Drawing.Point(709, 93);
            this.dateTimeZat.Name = "dateTimeZat";
            this.dateTimeZat.Size = new System.Drawing.Size(159, 20);
            this.dateTimeZat.TabIndex = 6;
            // 
            // txtPensja
            // 
            this.txtPensja.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.pracownikBindingSource, "pensja", true, System.Windows.Forms.DataSourceUpdateMode.OnValidation, "0", "C2"));
            this.txtPensja.Location = new System.Drawing.Point(709, 120);
            this.txtPensja.Name = "txtPensja";
            this.txtPensja.Size = new System.Drawing.Size(159, 20);
            this.txtPensja.TabIndex = 7;
            // 
            // cmbStan
            // 
            this.cmbStan.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", this.pracownikBindingSource, "id_stanowisko", true));
            this.cmbStan.DataSource = this.stanowiskoBindingSource1;
            this.cmbStan.DisplayMember = "nazwa";
            this.cmbStan.FormattingEnabled = true;
            this.cmbStan.Location = new System.Drawing.Point(709, 146);
            this.cmbStan.Name = "cmbStan";
            this.cmbStan.Size = new System.Drawing.Size(159, 21);
            this.cmbStan.TabIndex = 8;
            this.cmbStan.ValueMember = "id_stanowisko";
            // 
            // stanowiskoBindingSource1
            // 
            this.stanowiskoBindingSource1.DataMember = "stanowisko";
            this.stanowiskoBindingSource1.DataSource = this.dataSetbazaBindingSource;
            // 
            // dataSetbazaBindingSource
            // 
            this.dataSetbazaBindingSource.DataSource = this.dataSet_baza;
            this.dataSetbazaBindingSource.Position = 0;
            // 
            // lStanowisko
            // 
            this.lStanowisko.AutoSize = true;
            this.lStanowisko.Location = new System.Drawing.Point(642, 149);
            this.lStanowisko.Name = "lStanowisko";
            this.lStanowisko.Size = new System.Drawing.Size(62, 13);
            this.lStanowisko.TabIndex = 9;
            this.lStanowisko.Text = "Stanowisko";
            // 
            // lImie
            // 
            this.lImie.AutoSize = true;
            this.lImie.Location = new System.Drawing.Point(642, 17);
            this.lImie.Name = "lImie";
            this.lImie.Size = new System.Drawing.Size(26, 13);
            this.lImie.TabIndex = 10;
            this.lImie.Text = "Imie";
            this.lImie.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lNazwisko
            // 
            this.lNazwisko.AutoSize = true;
            this.lNazwisko.Location = new System.Drawing.Point(642, 48);
            this.lNazwisko.Name = "lNazwisko";
            this.lNazwisko.Size = new System.Drawing.Size(53, 13);
            this.lNazwisko.TabIndex = 11;
            this.lNazwisko.Text = "Nazwisko";
            // 
            // lDataUr
            // 
            this.lDataUr.AutoSize = true;
            this.lDataUr.Location = new System.Drawing.Point(643, 73);
            this.lDataUr.Name = "lDataUr";
            this.lDataUr.Size = new System.Drawing.Size(45, 13);
            this.lDataUr.TabIndex = 12;
            this.lDataUr.Text = "Data ur.";
            // 
            // lDataZat
            // 
            this.lDataZat.AutoSize = true;
            this.lDataZat.Location = new System.Drawing.Point(643, 99);
            this.lDataZat.Name = "lDataZat";
            this.lDataZat.Size = new System.Drawing.Size(53, 13);
            this.lDataZat.TabIndex = 13;
            this.lDataZat.Text = "Data zatr.";
            // 
            // lPensja
            // 
            this.lPensja.AutoSize = true;
            this.lPensja.Location = new System.Drawing.Point(643, 126);
            this.lPensja.Name = "lPensja";
            this.lPensja.Size = new System.Drawing.Size(39, 13);
            this.lPensja.TabIndex = 14;
            this.lPensja.Text = "Penjsa";
            // 
            // btnInsert
            // 
            this.btnInsert.Location = new System.Drawing.Point(646, 270);
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.Size = new System.Drawing.Size(75, 23);
            this.btnInsert.TabIndex = 15;
            this.btnInsert.Text = "Dodaj";
            this.btnInsert.UseVisualStyleBackColor = true;
            this.btnInsert.Click += new System.EventHandler(this.btnInsert_Click);
            // 
            // Pracownik
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(894, 330);
            this.Controls.Add(this.btnInsert);
            this.Controls.Add(this.lPensja);
            this.Controls.Add(this.lDataZat);
            this.Controls.Add(this.lDataUr);
            this.Controls.Add(this.lNazwisko);
            this.Controls.Add(this.lImie);
            this.Controls.Add(this.lStanowisko);
            this.Controls.Add(this.cmbStan);
            this.Controls.Add(this.txtPensja);
            this.Controls.Add(this.dateTimeZat);
            this.Controls.Add(this.dateTimeUr);
            this.Controls.Add(this.txtNazwisko);
            this.Controls.Add(this.txtImie);
            this.Controls.Add(this.btnUsun);
            this.Controls.Add(this.btnZapisz);
            this.Controls.Add(this.dataGridPracownik);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Pracownik";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Pracownik";
            this.Load += new System.EventHandler(this.Pracownik_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridPracownik)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.stanowiskoBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetbazaBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridPracownik;
        private DataSet_baza dataSet_baza;
        private System.Windows.Forms.BindingSource pracownikBindingSource;
        private DataSet_bazaTableAdapters.pracownikTableAdapter pracownikTableAdapter;
        private System.Windows.Forms.BindingSource stanowiskoBindingSource;
        private DataSet_bazaTableAdapters.stanowiskoTableAdapter stanowiskoTableAdapter;
        private System.Windows.Forms.Button btnZapisz;
        private System.Windows.Forms.Button btnUsun;
        private System.Windows.Forms.TextBox txtImie;
        private System.Windows.Forms.TextBox txtNazwisko;
        private System.Windows.Forms.DateTimePicker dateTimeUr;
        private System.Windows.Forms.DateTimePicker dateTimeZat;
        private System.Windows.Forms.TextBox txtPensja;
        private System.Windows.Forms.ComboBox cmbStan;
        private System.Windows.Forms.BindingSource stanowiskoBindingSource1;
        private System.Windows.Forms.BindingSource dataSetbazaBindingSource;
        private System.Windows.Forms.Label lStanowisko;
        private System.Windows.Forms.Label lImie;
        private System.Windows.Forms.Label lNazwisko;
        private System.Windows.Forms.Label lDataUr;
        private System.Windows.Forms.Label lDataZat;
        private System.Windows.Forms.Label lPensja;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.DataGridViewTextBoxColumn idpracownikDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn idstanowiskoDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn imieDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nazwiskoDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataurodzeniaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datazatrudnieniaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn pensjaDataGridViewTextBoxColumn;
    }
}