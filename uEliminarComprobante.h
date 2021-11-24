//---------------------------------------------------------------------------

#ifndef uEliminarComprobanteH
#define uEliminarComprobanteH
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
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TEliminarComprobante : public TForm
{
__published:	// IDE-managed Components
	TBevel *Bevel1;
	TLabel *Label1;
	TDBGrid *DBGrid1;
	TButton *Button1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TLabel *Label2;
	TEdit *EdContribuyente;
	TLabel *desContribuyente;
	TLabel *Label6;
	TEdit *EdPtoVenta;
	TLabel *Label3;
	TEdit *EdNroComprobante;
	TLabel *Label4;
	TEdit *EdFecha;
	TLabel *Label8;
	TEdit *EdDocumento;
	TLabel *desDocumento;
	TLabel *Label9;
	TEdit *EdTipo;
	TLabel *desTipo;
	TSQLQuery *AuxQuery;
	TRadioGroup *RG1;
	TButton *Button2;
	TDateField *ClientDataSet1fechaComprobante;
	TWideStringField *ClientDataSet1cliente;
	TWideStringField *ClientDataSet1desTipo;
	TWideStringField *ClientDataSet1desDocumento;
	TFMTBCDField *ClientDataSet1total;
	TIntegerField *ClientDataSet1ptoVenta;
	TIntegerField *ClientDataSet1nroComprobante;
	TButton *Button3;
	TIntegerField *ClientDataSet1idComprobanteVenta;
	TBevel *Bevel2;
	TLabel *Label5;
	TBevel *Bevel3;
	TLabel *Label7;
	TBevel *Bevel4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EdContribuyenteExit(TObject *Sender);
	void __fastcall EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPtoVentaExit(TObject *Sender);
	void __fastcall EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNroComprobanteExit(TObject *Sender);
	void __fastcall EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdFechaExit(TObject *Sender);
	void __fastcall EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdFechaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdDocumentoExit(TObject *Sender);
	void __fastcall EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdDocumentoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdTipoExit(TObject *Sender);
	void __fastcall EdTipoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdTipoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TEliminarComprobante(TComponent* Owner);

	void VerificarDatos(TObject *Sender);
	void SeleccionarTodo(TObject *Sender);
	void RestablecerFormulario(void);
	void Buscar(void);

	int idContribuyente;
	bool contOK, fechOK, ptoOK, nroOK, tipoOK, docOK;
};
//---------------------------------------------------------------------------
extern PACKAGE TEliminarComprobante *EliminarComprobante;
//---------------------------------------------------------------------------
#endif
