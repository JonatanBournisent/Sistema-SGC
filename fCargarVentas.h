//---------------------------------------------------------------------------

#ifndef fCargarVentasH
#define fCargarVentasH
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
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TCargarVentas : public TForm
{
__published:	// IDE-managed Components
	TEdit *EdAlicuota2;
	TSQLQuery *AuxQuery;
	TSQLQuery *SQLQuery1;
	TSQLConnection *SQLConnection1;
	TDataSetProvider *DataSetProvider1;
	TClientDataSet *ClientDataSet1;
	TDataSource *DataSource1;
	TButton *BtnAgregarYCont;
	TButton *BtnCancelar;
	TButton *BtnAgregarComp;
	TEdit *EdTipo;
	TEdit *EdDocumento;
	TEdit *EdAlicuota4;
	TEdit *EdAlicuota3;
	TEdit *EdAlicuota1;
	TEdit *EdFecha;
	TEdit *EdTotal;
	TEdit *EdExentos;
	TEdit *EdConcNoGravados;
	TEdit *EdCuentaVenta;
	TEdit *EdRetencionesGanancias;
	TEdit *EdPercepcionesIB;
	TEdit *EdRetencionesIB;
	TEdit *EdPercepcionesIVA;
	TEdit *EdRetencionesIVA;
	TEdit *EdNetoGravado4;
	TEdit *EdNetoGravado3;
	TEdit *EdNetoGravado2;
	TEdit *EdNetoGravado1;
	TEdit *EdNroComprobante;
	TEdit *EdPtoVenta;
	TEdit *EdPeriodo;
	TEdit *EdContribuyente;
	TEdit *EdCliente;
	TLabel *Label21;
	TLabel *Label20;
	TLabel *Label19;
	TLabel *Label18;
	TLabel *Label17;
	TLabel *Label16;
	TLabel *Label15;
	TLabel *Label14;
	TLabel *Label13;
	TLabel *Label12;
	TLabel *Label11;
	TLabel *Label10;
	TLabel *Label9;
	TLabel *Label8;
	TLabel *Label7;
	TLabel *Label6;
	TLabel *Label5;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *desTipo;
	TLabel *desDocumento;
	TLabel *desCuentaVenta;
	TLabel *Label1;
	TLabel *desAlicuota4;
	TLabel *desAlicuota3;
	TLabel *desAlicuota2;
	TLabel *desAlicuota1;
	TLabel *desCliente;
	TLabel *desContribuyente;
	TCheckBox *ChAnulado;
	TButton *AgCliente;
	TLabel *LabIVA1;
	TLabel *LabIVA2;
	TLabel *LabIVA3;
	TLabel *LabIVA4;
	TLabel *Label23;
	TEdit *EdJurisdiccion;
	TLabel *Label24;
	TLabel *desJurisdiccion;
	TRadioGroup *RG1;
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
	void __fastcall EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdClienteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdClienteKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdClienteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdClienteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdPeriodoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdFechaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EdFechaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdCuentaVentaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdTipoKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall BtnAgregarCompClick(TObject *Sender);
	void __fastcall EdClienteExit(TObject *Sender);
	void __fastcall EdPtoVentaExit(TObject *Sender);
	void __fastcall EdNroComprobanteExit(TObject *Sender);
	void __fastcall EdDocumentoExit(TObject *Sender);
	void __fastcall EdTipoExit(TObject *Sender);
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
	void __fastcall EdTotalEnter(TObject *Sender);
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
	void __fastcall EdExentosExit(TObject *Sender);
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
	void __fastcall BtnAgregarYContClick(TObject *Sender);
	void __fastcall BtnCancelarClick(TObject *Sender);
	void __fastcall EdContribuyenteExit(TObject *Sender);
	void __fastcall EdPeriodoExit(TObject *Sender);
	void __fastcall EdFechaExit(TObject *Sender);
	void __fastcall EdCuentaVentaExit(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EdTotalExit(TObject *Sender);
	void __fastcall AgClienteClick(TObject *Sender);
	void __fastcall EdAlicuota1Exit(TObject *Sender);
	void __fastcall EdAlicuota2Exit(TObject *Sender);
	void __fastcall EdAlicuota3Exit(TObject *Sender);
	void __fastcall EdAlicuota4Exit(TObject *Sender);
	void __fastcall EdAlicuota1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota3MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdAlicuota4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdCuentaVentaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdDocumentoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdTipoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EdJurisdiccionExit(TObject *Sender);
	void __fastcall EdJurisdiccionMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall RG1Click(TObject *Sender);
	void __fastcall btEliminarCompClick(TObject *Sender);
	void __fastcall btMostrarCompClick(TObject *Sender);
	void __fastcall btEliminarCompExit(TObject *Sender);
	void __fastcall BtnCancelarExit(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TCargarVentas(TComponent* Owner);

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
	int idContribuyente, idCliente;
	int civaCont, civaCli;
	float IVA1, IVA2, IVA3, IVA4;
	float ali1, ali2, ali3, ali4;
	bool contOK, perOK, fechOK, cliOK, ptoOK, nroOK, ccOK, tipoOK, docOK, juriOK, al1OK, al2OK, al3OK, al4OK;
};
//---------------------------------------------------------------------------
extern PACKAGE TCargarVentas *CargarVentas;
//---------------------------------------------------------------------------
#endif
