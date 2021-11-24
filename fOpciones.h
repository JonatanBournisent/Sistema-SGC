//---------------------------------------------------------------------------

#ifndef fOpcionesH
#define fOpcionesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DBXMySQL.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOpciones : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGrid1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *Query1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button1;
	TBevel *Bevel1;
	TBevel *Bevel2;
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DBGrid1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOpciones(TComponent* Owner);


	int llamador;  //indica quien lo llama para saber que mostrar
	// 1: Cuentas Compra
	// 2: Cuentas Venta
	// 3: Documentos
	// 4: Tipo documento
	// 5: Jurisdicciones
	// 6: Condiciones IVA
	// 7: Contribuyentes
	int idRetorno;
	bool soloMisClientes;
};
//---------------------------------------------------------------------------
extern PACKAGE TOpciones *Opciones;
//---------------------------------------------------------------------------
#endif
