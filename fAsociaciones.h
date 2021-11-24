//---------------------------------------------------------------------------

#ifndef fAsociacionesH
#define fAsociacionesH
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
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAsociaciones : public TForm
{
__published:	// IDE-managed Components
	TEdit *EdContribuyente;
	TEdit *EdAsociado;
	TLabel *desContribuyente;
	TLabel *desAsociado;
	TLabel *Label2;
	TLabel *Label5;
	TLabel *Label7;
	TEdit *EdCuenta;
	TLabel *desCuenta;
	TSQLQuery *AuxQuery;
	TSQLConnection *SQLConnection1;
	TClientDataSet *ClientDataSet1;
	TDataSetProvider *DataSetProvider1;
	TSQLQuery *Query1;
	TButton *BtnGuardar;
	TButton *BtnCancelar;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TRadioGroup *RG;
	void __fastcall EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdAsociadoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdAsociadoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdAsociadoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAsociadoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdContribuyenteExit(TObject *Sender);
	void __fastcall EdAsociadoExit(TObject *Sender);
	void __fastcall EdCuentaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdCuentaExit(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnGuardarClick(TObject *Sender);
	void __fastcall BtnCancelarClick(TObject *Sender);
	void __fastcall RGClick(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TAsociaciones(TComponent* Owner);


	void VerificarDatos(TObject *Sender);
	void RestablecerFormulario(void);

	bool ccOK, asocOK, contOK;
	int idContribuyente, idAsociado;
	int llamador;
	// 1: asociar cliente a contribuyente
	// 2: asociar proveedor a contribuyente
};
//---------------------------------------------------------------------------
extern PACKAGE TAsociaciones *Asociaciones;
//---------------------------------------------------------------------------
#endif
