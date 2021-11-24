//---------------------------------------------------------------------------

#ifndef fCargarComprasH
#define fCargarComprasH
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
#include <Vcl.Mask.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TCargarCompras : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
	TClientDataSet *ClientDataSet1;
	TDataSetProvider *DataSetProvider1;
	TSQLConnection *SQLConnection1;
	TSQLQuery *SQLQuery1;
	TEdit *EdProveedor;
	TEdit *EdContribuyente;
	TEdit *EdPeriodo;
	TEdit *EdPtoVenta;
	TEdit *EdNroComprobante;
	TEdit *EdNetoGravado1;
	TEdit *EdNetoGravado2;
	TEdit *EdNetoGravado3;
	TEdit *EdNetoGravado4;
	TEdit *EdRetencionesIVA;
	TEdit *EdPercepcionesIVA;
	TEdit *EdRetencionesIB;
	TEdit *EdPercepcionesIB;
	TEdit *EdRetencionesGanancias;
	TEdit *EdCuentaCompra;
	TEdit *EdConcNoGravados;
	TEdit *EdExentos;
	TEdit *EdTotal;
	TEdit *EdFecha;
	TSQLQuery *AuxQuery;
	TLabel *desContribuyente;
	TLabel *desProveedor;
	TLabel *desAlicuota1;
	TLabel *desAlicuota2;
	TLabel *desAlicuota3;
	TLabel *desAlicuota4;
	TEdit *EdAlicuota1;
	TEdit *EdAlicuota2;
	TEdit *EdAlicuota3;
	TEdit *EdAlicuota4;
	TEdit *EdDocumento;
	TEdit *EdTipo;
	TLabel *Label1;
	TLabel *desCuentaCompra;
	TLabel *desDocumento;
	TLabel *desTipo;
	TButton *BtnAgregarComp;
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
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TButton *BtnCancelar;
	TButton *BtnAgregarYCont;
	TButton *AgProveedor;
	TLabel *LabIVA1;
	TLabel *LabIVA2;
	TLabel *LabIVA3;
	TLabel *LabIVA4;
	TLabel *Label23;
	TEdit *EdJurisdiccion;
	TLabel *Label24;
	TLabel *desJurisdiccion;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TButton *btEliminarComp;
	TSpeedButton *btMostrarComp;
	TBevel *Bevel5;
	TSpeedButton *SpeedButton1;
	TEdit *Edit1;
	TEdit *Edit2;
	void __fastcall BtnAgregarCompClick(TObject *Sender);
	void __fastcall EdFechaExit(TObject *Sender);
	void __fastcall EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdFechaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdFechaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPeriodoExit(TObject *Sender);
	void __fastcall EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdProveedorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdProveedorKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdProveedorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdProveedorMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdProveedorExit(TObject *Sender);
	void __fastcall EdCuentaCompraExit(TObject *Sender);
	void __fastcall EdDocumentoExit(TObject *Sender);
	void __fastcall EdTipoExit(TObject *Sender);
	void __fastcall EdExentosExit(TObject *Sender);
	void __fastcall EdNetoGravado1Exit(TObject *Sender);
	void __fastcall EdNetoGravado2Exit(TObject *Sender);
	void __fastcall EdNetoGravado3Exit(TObject *Sender);
	void __fastcall EdNetoGravado4Exit(TObject *Sender);
	void __fastcall EdRetencionesIVAExit(TObject *Sender);
	void __fastcall EdPercepcionesIVAExit(TObject *Sender);
	void __fastcall EdRetencionesIBExit(TObject *Sender);
	void __fastcall EdPercepcionesIBExit(TObject *Sender);
	void __fastcall EdRetencionesGananciasExit(TObject *Sender);
	void __fastcall EdConcNoGravadosExit(TObject *Sender);
	void __fastcall EdNetoGravado1Enter(TObject *Sender);
	void __fastcall EdNetoGravado2Enter(TObject *Sender);
	void __fastcall EdNetoGravado3Enter(TObject *Sender);
	void __fastcall EdNetoGravado4Enter(TObject *Sender);
	void __fastcall EdRetencionesIVAEnter(TObject *Sender);
	void __fastcall EdPercepcionesIVAEnter(TObject *Sender);
	void __fastcall EdRetencionesIBEnter(TObject *Sender);
	void __fastcall EdPercepcionesIBEnter(TObject *Sender);
	void __fastcall EdRetencionesGananciasEnter(TObject *Sender);
	void __fastcall EdConcNoGravadosEnter(TObject *Sender);
	void __fastcall EdExentosEnter(TObject *Sender);
	void __fastcall EdNetoGravado1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdNetoGravado2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdNetoGravado3KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdNetoGravado4KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdRetencionesIVAKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPercepcionesIVAKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdRetencionesIBKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPercepcionesIBKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdRetencionesGananciasKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdConcNoGravadosKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdExentosKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdTotalKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdNetoGravado1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNetoGravado2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNetoGravado3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNetoGravado4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdRetencionesIVAMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPercepcionesIVAMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdRetencionesIBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPercepcionesIBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdRetencionesGananciasMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall EdConcNoGravadosMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdExentosMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdTotalMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdContribuyenteExit(TObject *Sender);
	void __fastcall EdPtoVentaExit(TObject *Sender);
	void __fastcall EdNroComprobanteExit(TObject *Sender);
	void __fastcall EdTotalEnter(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnCancelarClick(TObject *Sender);
	void __fastcall BtnAgregarYContClick(TObject *Sender);
	void __fastcall EdCuentaCompraKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdTipoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdTotalExit(TObject *Sender);
	void __fastcall AgProveedorClick(TObject *Sender);
	void __fastcall EdAlicuota1Exit(TObject *Sender);
	void __fastcall EdAlicuota2Exit(TObject *Sender);
	void __fastcall EdAlicuota3Exit(TObject *Sender);
	void __fastcall EdAlicuota4Exit(TObject *Sender);
	void __fastcall EdCuentaCompraMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdDocumentoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdTipoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdJurisdiccionExit(TObject *Sender);
	void __fastcall EdJurisdiccionMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btEliminarCompClick(TObject *Sender);
	void __fastcall btMostrarCompClick(TObject *Sender);
	void __fastcall BtnCancelarExit(TObject *Sender);
	void __fastcall btEliminarCompExit(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TCargarCompras(TComponent* Owner);


	void LimpiarEdit(TObject *Sender);
	void DarFormatoEdit(TObject *Sender);
	void DarFormatoEntrada(System::WideChar &Key);
	void SeleccionarTodo(TObject *Sender);
	void VerificarDatos(TObject *Sender);
	void ActualizarTotal(void);
	int YaExiste(void);
	void TraerDatos(int idCompCompra);
	void RestablecerFormulario(void);
	void RestablecerFormularioCont(void);
	bool GuardarDatos(void);
	void QuiereModificar(TObject *Sender);
	void CalcularIVA(TObject *Sender);
	AnsiString LimpiarNumero(AnsiString s);

	bool modificando; //se trada de una edicion de datos y no una agregacion
	int idModificado;
	int idContribuyente, idProveedor;
	int civaProv, civaCont;
	float IVA1, IVA2, IVA3, IVA4;
	float ali1, ali2, ali3, ali4;
	bool contOK, perOK, fechOK, provOK, ptoOK, nroOK, ccOK, tipoOK, docOK, juriOK, al1OK, al2OK, al3OK, al4OK;
};
//---------------------------------------------------------------------------
extern PACKAGE TCargarCompras *CargarCompras;
//---------------------------------------------------------------------------
#endif
