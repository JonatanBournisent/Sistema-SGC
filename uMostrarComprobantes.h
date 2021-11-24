//---------------------------------------------------------------------------

#ifndef uMostrarComprobantesH
#define uMostrarComprobantesH
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
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TfMostrarComprobantes : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TDBGrid *DBG1;
	TSQLQuery *AuxQuery;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *CDS;
	TDateField *CDSfechaComprobante;
	TIntegerField *CDSptoVenta;
	TIntegerField *CDSnroComprobante;
	TWideStringField *CDSproveedor;
	TFMTBCDField *CDSnetoGravado1;
	TFMTBCDField *CDSnetoGravado2;
	TFMTBCDField *CDSnetoGravado3;
	TFMTBCDField *CDSretencionesIVA;
	TFMTBCDField *CDSpercepcionesIVA;
	TFMTBCDField *CDSretencionesIB;
	TFMTBCDField *CDSpercepcionesIB;
	TFMTBCDField *CDSretencionesGanancias;
	TFMTBCDField *CDSconceptosNoGravados;
	TFMTBCDField *CDSexentos;
	TWideStringField *CDSdesTipo;
	TWideStringField *CDSdesDocumento;
	TWideStringField *CDSdesCuentaCompra;
	TWideStringField *CDSdesJurisdiccion;
	TIntegerField *CDSidTipo;
	TIntegerField *CDSidDocumento;
	TWideStringField *CDScuit;
	TFMTBCDField *CDStotal;
	TDataSource *DataSource1;
	TIntegerField *CDSidComprobanteCompra;
	TFMTBCDField *CDStotIVA;
	TButton *Button3;
	TEdit *EdPeriodo;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Modificarfecha1Click(TObject *Sender);
	void __fastcall EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPeriodoExit(TObject *Sender);
	void __fastcall DBG1DblClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfMostrarComprobantes(TComponent* Owner);

	void VerificarDatos(TObject *Sender);

    bool perOK;
	int idContribuyente;
	AnsiString periodo;
	int llamador;   // 0: Comprobantes ventas
					// 1: Comprobantes compras

	int retorno; // contiene el id del comprobante seleccionado;
	bool modificando;

};
//---------------------------------------------------------------------------
extern PACKAGE TfMostrarComprobantes *fMostrarComprobantes;
//---------------------------------------------------------------------------
#endif
