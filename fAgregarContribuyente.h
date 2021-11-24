//---------------------------------------------------------------------------

#ifndef fAgregarContribuyenteH
#define fAgregarContribuyenteH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Data.DBXMySQL.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TAgregarContribuyente : public TForm
{
__published:	// IDE-managed Components
	TEdit *EdCUIT;
	TSQLQuery *AuxQuery;
	TSQLConnection *SQLConnection1;
	TEdit *EdRazonSocial;
	TButton *BtnGuardar;
	TEdit *EdCondIVA;
	TEdit *EdJurisdiccion;
	TComboBox *CBCliente;
	TButton *BtnCancelar;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *desCondIVA;
	TLabel *desJurisdiccion;
	TClientDataSet *ClientDataSet1;
	TDataSetProvider *DataSetProvider1;
	TSQLQuery *Query1;
	TEdit *EdCuenta;
	TLabel *Label7;
	TLabel *desCuenta;
	TBevel *Bevel1;
	TSpeedButton *SpeedButton1;
	void __fastcall EdCUITKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdCUITKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdCUITKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdCUITExit(TObject *Sender);
	void __fastcall BtnCancelarClick(TObject *Sender);
	void __fastcall EdCondIVAExit(TObject *Sender);
	void __fastcall EdJurisdiccionExit(TObject *Sender);
	void __fastcall BtnGuardarClick(TObject *Sender);
	void __fastcall EdRazonSocialExit(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EdCuentaExit(TObject *Sender);
	void __fastcall EdCondIVAKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdCuentaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);



private:	// User declarations
public:		// User declarations
	__fastcall TAgregarContribuyente(TComponent* Owner);

	void VerificarDatos(TObject *Sender);

	void RestablecerFormulario(void);
	int YaExiste(AnsiString cuit); // si existe retorna el id, si no retorna 0

	bool modificando;
	int idModificado;
	int llamador; //1: llamo para agregar contribuyente, 2: llamo desde cargar compras, 3: cargar ventas
	int idContribuyente; //sirve para llamador 2 y 3 (para relacionar clientes-contrib y proveed-contrib
	bool cuitOK, razonOK, civaOK, jurOK, ctaOK;
	AnsiString cuitOLD;
};
//---------------------------------------------------------------------------
extern PACKAGE TAgregarContribuyente *AgregarContribuyente;
//---------------------------------------------------------------------------
#endif
