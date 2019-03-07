namespace Company
{
    partial class Zadania
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
            this.dataGridViewZadania = new System.Windows.Forms.DataGridView();
            this.idprojektDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.projektBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.dataSet_baza = new Company.DataSet_baza();
            this.idpracownikDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.pracownikBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.stawkaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.iloscgodzinDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.komentarzDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datastartuDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.datakoncaDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.zadaniapracownikowBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.zadania_pracownikowTableAdapter = new Company.DataSet_bazaTableAdapters.zadania_pracownikowTableAdapter();
            this.projektTableAdapter = new Company.DataSet_bazaTableAdapters.projektTableAdapter();
            this.pracownikTableAdapter = new Company.DataSet_bazaTableAdapters.pracownikTableAdapter();
            this.cmbProjekt = new System.Windows.Forms.ComboBox();
            this.cmbPrac = new System.Windows.Forms.ComboBox();
            this.txtStawka = new System.Windows.Forms.TextBox();
            this.txtKom = new System.Windows.Forms.TextBox();
            this.dateTimeStart = new System.Windows.Forms.DateTimePicker();
            this.dateTimeKon = new System.Windows.Forms.DateTimePicker();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.btnInsert = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnUsun = new System.Windows.Forms.Button();
            this.projektBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.pracownikBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.numGodziny = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewZadania)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.zadaniapracownikowBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numGodziny)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewZadania
            // 
            this.dataGridViewZadania.AllowUserToAddRows = false;
            this.dataGridViewZadania.AllowUserToOrderColumns = true;
            this.dataGridViewZadania.AutoGenerateColumns = false;
            this.dataGridViewZadania.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewZadania.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewZadania.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idprojektDataGridViewTextBoxColumn,
            this.idpracownikDataGridViewTextBoxColumn,
            this.stawkaDataGridViewTextBoxColumn,
            this.iloscgodzinDataGridViewTextBoxColumn,
            this.komentarzDataGridViewTextBoxColumn,
            this.datastartuDataGridViewTextBoxColumn,
            this.datakoncaDataGridViewTextBoxColumn});
            this.dataGridViewZadania.DataSource = this.zadaniapracownikowBindingSource;
            this.dataGridViewZadania.Location = new System.Drawing.Point(12, 12);
            this.dataGridViewZadania.Name = "dataGridViewZadania";
            this.dataGridViewZadania.Size = new System.Drawing.Size(618, 306);
            this.dataGridViewZadania.TabIndex = 0;
            // 
            // idprojektDataGridViewTextBoxColumn
            // 
            this.idprojektDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.idprojektDataGridViewTextBoxColumn.DataPropertyName = "id_projekt";
            this.idprojektDataGridViewTextBoxColumn.DataSource = this.projektBindingSource;
            this.idprojektDataGridViewTextBoxColumn.DisplayMember = "nazwa";
            this.idprojektDataGridViewTextBoxColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.Nothing;
            this.idprojektDataGridViewTextBoxColumn.HeaderText = "projekt";
            this.idprojektDataGridViewTextBoxColumn.Name = "idprojektDataGridViewTextBoxColumn";
            this.idprojektDataGridViewTextBoxColumn.ReadOnly = true;
            this.idprojektDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.idprojektDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.idprojektDataGridViewTextBoxColumn.ValueMember = "id_projekt";
            this.idprojektDataGridViewTextBoxColumn.Width = 64;
            // 
            // projektBindingSource
            // 
            this.projektBindingSource.DataMember = "projekt";
            this.projektBindingSource.DataSource = this.dataSet_baza;
            // 
            // dataSet_baza
            // 
            this.dataSet_baza.DataSetName = "DataSet_baza";
            this.dataSet_baza.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // idpracownikDataGridViewTextBoxColumn
            // 
            this.idpracownikDataGridViewTextBoxColumn.DataPropertyName = "id_pracownik";
            this.idpracownikDataGridViewTextBoxColumn.DataSource = this.pracownikBindingSource;
            this.idpracownikDataGridViewTextBoxColumn.DisplayMember = "FullName";
            this.idpracownikDataGridViewTextBoxColumn.DisplayStyle = System.Windows.Forms.DataGridViewComboBoxDisplayStyle.Nothing;
            this.idpracownikDataGridViewTextBoxColumn.HeaderText = "pracownik";
            this.idpracownikDataGridViewTextBoxColumn.Name = "idpracownikDataGridViewTextBoxColumn";
            this.idpracownikDataGridViewTextBoxColumn.ReadOnly = true;
            this.idpracownikDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.idpracownikDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.idpracownikDataGridViewTextBoxColumn.ValueMember = "id_pracownik";
            // 
            // pracownikBindingSource
            // 
            this.pracownikBindingSource.DataMember = "pracownik";
            this.pracownikBindingSource.DataSource = this.dataSet_baza;
            // 
            // stawkaDataGridViewTextBoxColumn
            // 
            this.stawkaDataGridViewTextBoxColumn.DataPropertyName = "stawka";
            this.stawkaDataGridViewTextBoxColumn.HeaderText = "stawka";
            this.stawkaDataGridViewTextBoxColumn.Name = "stawkaDataGridViewTextBoxColumn";
            // 
            // iloscgodzinDataGridViewTextBoxColumn
            // 
            this.iloscgodzinDataGridViewTextBoxColumn.DataPropertyName = "ilosc_godzin";
            this.iloscgodzinDataGridViewTextBoxColumn.HeaderText = "ilosc_godzin";
            this.iloscgodzinDataGridViewTextBoxColumn.Name = "iloscgodzinDataGridViewTextBoxColumn";
            // 
            // komentarzDataGridViewTextBoxColumn
            // 
            this.komentarzDataGridViewTextBoxColumn.DataPropertyName = "komentarz";
            this.komentarzDataGridViewTextBoxColumn.HeaderText = "komentarz";
            this.komentarzDataGridViewTextBoxColumn.Name = "komentarzDataGridViewTextBoxColumn";
            // 
            // datastartuDataGridViewTextBoxColumn
            // 
            this.datastartuDataGridViewTextBoxColumn.DataPropertyName = "data_startu";
            this.datastartuDataGridViewTextBoxColumn.HeaderText = "data_startu";
            this.datastartuDataGridViewTextBoxColumn.Name = "datastartuDataGridViewTextBoxColumn";
            // 
            // datakoncaDataGridViewTextBoxColumn
            // 
            this.datakoncaDataGridViewTextBoxColumn.DataPropertyName = "data_konca";
            this.datakoncaDataGridViewTextBoxColumn.HeaderText = "data_konca";
            this.datakoncaDataGridViewTextBoxColumn.Name = "datakoncaDataGridViewTextBoxColumn";
            // 
            // zadaniapracownikowBindingSource
            // 
            this.zadaniapracownikowBindingSource.DataMember = "zadania_pracownikow";
            this.zadaniapracownikowBindingSource.DataSource = this.dataSet_baza;
            // 
            // zadania_pracownikowTableAdapter
            // 
            this.zadania_pracownikowTableAdapter.ClearBeforeFill = true;
            // 
            // projektTableAdapter
            // 
            this.projektTableAdapter.ClearBeforeFill = true;
            // 
            // pracownikTableAdapter
            // 
            this.pracownikTableAdapter.ClearBeforeFill = true;
            // 
            // cmbProjekt
            // 
            this.cmbProjekt.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", this.zadaniapracownikowBindingSource, "id_projekt", true));
            this.cmbProjekt.DataSource = this.projektBindingSource1;
            this.cmbProjekt.DisplayMember = "nazwa";
            this.cmbProjekt.FormattingEnabled = true;
            this.cmbProjekt.Location = new System.Drawing.Point(709, 14);
            this.cmbProjekt.Name = "cmbProjekt";
            this.cmbProjekt.Size = new System.Drawing.Size(159, 21);
            this.cmbProjekt.TabIndex = 1;
            this.cmbProjekt.ValueMember = "id_projekt";
            // 
            // cmbPrac
            // 
            this.cmbPrac.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", this.zadaniapracownikowBindingSource, "id_pracownik", true));
            this.cmbPrac.DataSource = this.pracownikBindingSource1;
            this.cmbPrac.DisplayMember = "FullName";
            this.cmbPrac.FormattingEnabled = true;
            this.cmbPrac.Location = new System.Drawing.Point(709, 42);
            this.cmbPrac.Name = "cmbPrac";
            this.cmbPrac.Size = new System.Drawing.Size(159, 21);
            this.cmbPrac.TabIndex = 2;
            this.cmbPrac.ValueMember = "id_pracownik";
            // 
            // txtStawka
            // 
            this.txtStawka.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.zadaniapracownikowBindingSource, "stawka", true, System.Windows.Forms.DataSourceUpdateMode.OnValidation, null, "C2"));
            this.txtStawka.Location = new System.Drawing.Point(709, 70);
            this.txtStawka.Name = "txtStawka";
            this.txtStawka.Size = new System.Drawing.Size(159, 20);
            this.txtStawka.TabIndex = 3;
            // 
            // txtKom
            // 
            this.txtKom.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.zadaniapracownikowBindingSource, "komentarz", true));
            this.txtKom.Location = new System.Drawing.Point(709, 124);
            this.txtKom.Name = "txtKom";
            this.txtKom.Size = new System.Drawing.Size(159, 20);
            this.txtKom.TabIndex = 5;
            // 
            // dateTimeStart
            // 
            this.dateTimeStart.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.zadaniapracownikowBindingSource, "data_startu", true));
            this.dateTimeStart.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeStart.Location = new System.Drawing.Point(709, 151);
            this.dateTimeStart.Name = "dateTimeStart";
            this.dateTimeStart.Size = new System.Drawing.Size(159, 20);
            this.dateTimeStart.TabIndex = 6;
            // 
            // dateTimeKon
            // 
            this.dateTimeKon.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.zadaniapracownikowBindingSource, "data_konca", true));
            this.dateTimeKon.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimeKon.Location = new System.Drawing.Point(709, 178);
            this.dateTimeKon.Name = "dateTimeKon";
            this.dateTimeKon.Size = new System.Drawing.Size(159, 20);
            this.dateTimeKon.TabIndex = 7;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(637, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Projekt";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(637, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Pracownik";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(637, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Stawka";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(637, 103);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Il. godzin";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(636, 131);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(57, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Komentarz";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(637, 157);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "Data startu";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(637, 184);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(63, 13);
            this.label7.TabIndex = 14;
            this.label7.Text = "Data końca";
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
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(728, 269);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 16;
            this.btnSave.Text = "Edytuj";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnUsun
            // 
            this.btnUsun.Location = new System.Drawing.Point(810, 268);
            this.btnUsun.Name = "btnUsun";
            this.btnUsun.Size = new System.Drawing.Size(75, 23);
            this.btnUsun.TabIndex = 17;
            this.btnUsun.Text = "Usuń";
            this.btnUsun.UseVisualStyleBackColor = true;
            this.btnUsun.Click += new System.EventHandler(this.btnUsun_Click);
            // 
            // projektBindingSource1
            // 
            this.projektBindingSource1.DataMember = "projekt";
            this.projektBindingSource1.DataSource = this.dataSet_baza;
            // 
            // pracownikBindingSource1
            // 
            this.pracownikBindingSource1.DataMember = "pracownik";
            this.pracownikBindingSource1.DataSource = this.dataSet_baza;
            // 
            // numGodziny
            // 
            this.numGodziny.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.zadaniapracownikowBindingSource, "ilosc_godzin", true));
            this.numGodziny.Location = new System.Drawing.Point(709, 97);
            this.numGodziny.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numGodziny.Name = "numGodziny";
            this.numGodziny.Size = new System.Drawing.Size(159, 20);
            this.numGodziny.TabIndex = 4;
            this.numGodziny.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // Zadania
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 330);
            this.Controls.Add(this.btnUsun);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnInsert);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dateTimeKon);
            this.Controls.Add(this.dateTimeStart);
            this.Controls.Add(this.txtKom);
            this.Controls.Add(this.numGodziny);
            this.Controls.Add(this.txtStawka);
            this.Controls.Add(this.cmbPrac);
            this.Controls.Add(this.cmbProjekt);
            this.Controls.Add(this.dataGridViewZadania);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Zadania";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Zadania";
            this.Load += new System.EventHandler(this.Zadania_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewZadania)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSet_baza)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.zadaniapracownikowBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.projektBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pracownikBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numGodziny)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewZadania;
        private DataSet_baza dataSet_baza;
        private System.Windows.Forms.BindingSource zadaniapracownikowBindingSource;
        private DataSet_bazaTableAdapters.zadania_pracownikowTableAdapter zadania_pracownikowTableAdapter;
        private System.Windows.Forms.BindingSource projektBindingSource;
        private DataSet_bazaTableAdapters.projektTableAdapter projektTableAdapter;
        private System.Windows.Forms.BindingSource pracownikBindingSource;
        private DataSet_bazaTableAdapters.pracownikTableAdapter pracownikTableAdapter;
        private System.Windows.Forms.DataGridViewComboBoxColumn idprojektDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn idpracownikDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn stawkaDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn iloscgodzinDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn komentarzDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datastartuDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn datakoncaDataGridViewTextBoxColumn;
        private System.Windows.Forms.ComboBox cmbProjekt;
        private System.Windows.Forms.ComboBox cmbPrac;
        private System.Windows.Forms.TextBox txtStawka;
        private System.Windows.Forms.TextBox txtKom;
        private System.Windows.Forms.DateTimePicker dateTimeStart;
        private System.Windows.Forms.DateTimePicker dateTimeKon;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnUsun;
        private System.Windows.Forms.BindingSource projektBindingSource1;
        private System.Windows.Forms.BindingSource pracownikBindingSource1;
        private System.Windows.Forms.NumericUpDown numGodziny;
    }
}