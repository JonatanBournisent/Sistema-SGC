//---------------------------------------------------------------------------

#ifndef fReportesH
#define fReportesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TReportes : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS;
	TDataSource *DataSource1;
	TDBGrid *DBG1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TSQLQuery *AuxQuery;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TEdit *EdContribuyente;
	TLabel *desContribuyente;
	TEdit *EdPeriodo;
	TRadioGroup *RG1;
	TComboBox *CB1;
	TComboBox *CB2;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TDateField *CDSfechaComprobante;
	TIntegerField *CDSptoVenta;
	TIntegerField *CDSnroComprobante;
	TFMTBCDField *CDSnetoGravado1;
	TFMTBCDField *CDSnetoGravado2;
	TFMTBCDField *CDSnetoGravado3;
	TFMTBCDField *CDSretencionesIVA;
	TFMTBCDField *CDSretencionesIB;
	TFMTBCDField *CDSpercepcionesIVA;
	TFMTBCDField *CDSpercepcionesIB;
	TFMTBCDField *CDSretencionesGanancias;
	TFMTBCDField *CDSconceptosNoGravados;
	TFMTBCDField *CDSexentos;
	TWideStringField *CDSproveedor;
	TWideStringField *CDSdesTipo;
	TWideStringField *CDSdesDocumento;
	TWideStringField *CDSdesCuentaCompra;
	TWideStringField *CDSdesJurisdiccion;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TBevel *Bevel5;
	TBevel *Bevel6;
	TBevel *Bevel7;
	TBevel *Bevel8;
	TBevel *Bevel9;
	TBevel *Bevel10;
	TBevel *Bevel11;
	TBevel *Bevel12;
	TBevel *Bevel13;
	TBevel *Bevel14;
	TBevel *Bevel15;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label36;
	TBevel *Bevel17;
	TLabel *Label38;
	TEdit *EdProCli;
	TLabel *desProCli;
	TBevel *Bevel16;
	TButton *Button3;
	TIntegerField *CDSidTipo;
	TIntegerField *CDSidDocumento;
	TWideStringField *CDScuit;
	TFMTBCDField *CDStotal;
	TLabel *Label1;
	TLabel *Label37;
	TButton *Button4;
	TSaveDialog *SaveDialog1;
	TBevel *Bevel18;
	TBevel *Bevel19;
	TCheckBox *CkB1;
	TCheckBox *CkB2;
	TCheckBox *CkB3;
	TCheckBox *CkB4;
	TCheckBox *CkB5;
	TButton *Button2;
	TFMTBCDField *CDStotIVA;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label39;
	TLabel *Label40;
	TBevel *Bevel20;
	TUpDown *UpDown1;
	void __fastcall EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdContribuyenteExit(TObject *Sender);
	void __fastcall EdPeriodoExit(TObject *Sender);
	void __fastcall EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CB1Change(TObject *Sender);
	void __fastcall CB2Change(TObject *Sender);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall EdProCliKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdProCliKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdProCliKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdProCliMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdProCliExit(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall EdContribuyenteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall CkB1Click(TObject *Sender);
	void __fastcall CkB2Click(TObject *Sender);
	void __fastcall CkB3Click(TObject *Sender);
	void __fastcall CkB4Click(TObject *Sender);
	void __fastcall CkB5Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);





private:	// User declarations
public:		// User declarations
	__fastcall TReportes(TComponent* Owner);


	void VerificarDatos(TObject *Sender);
	void Buscar(void);
	void CargarJurisdicciones(void);
	void CargarCuentas(void);
	void Mostrar(void);
	void RestablecerFormulario(void);

	int idContribuyente;
	int idProCli;
	int j;
	bool perOK, conOK, procliOK;
};
//---------------------------------------------------------------------------
extern PACKAGE TReportes *Reportes;
//---------------------------------------------------------------------------
#endif
