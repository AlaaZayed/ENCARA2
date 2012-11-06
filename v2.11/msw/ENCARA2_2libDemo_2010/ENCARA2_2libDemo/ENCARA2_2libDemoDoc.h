
// ENCARA2_2libDemoDoc.h: interfaz de la clase CENCARA2_2libDemoDoc
//


#pragma once


class CENCARA2_2libDemoDoc : public CDocument
{
protected: // Crear s�lo a partir de serializaci�n
	CENCARA2_2libDemoDoc();
	DECLARE_DYNCREATE(CENCARA2_2libDemoDoc)

// Atributos
public:

// Operaciones
public:

// Reemplazos
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementaci�n
public:
	virtual ~CENCARA2_2libDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Funciones de asignaci�n de mensajes generadas
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Funci�n auxiliar que establece contenido de b�squeda para un controlador de b�squeda
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
