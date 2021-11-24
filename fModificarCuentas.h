//---------------------------------------------------------------------------

#ifndef fModificarCuentasH
#define fModificarCuentasH
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
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TModificarCuentas : public TForm
{
__published:	// IDE-managed Components
	TSQLConnection *SQLConnection1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDBGrid *DBGrid1;
	TRadioGroup *RG;
	TDataSource *DataSource1;
	TButton *Button1;
	TButton *Button2;
	TSQLQuery *AuxQuery;
	TEdit *Edit1;
	TSQLQuery *Query1;
	TBevel *Bevel1;
	void __fastcall RGClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TModificarCuentas(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModificarCuentas *ModificarCuentas;
//---------------------------------------------------------------------------
#endif
