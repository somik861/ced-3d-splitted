/************************************************************************/
/*																		*/
/* Author			Philippe Thevenaz									*/
/* Affiliation		Ecole polytechnique federale de Lausanne			*/
/*					DMT/IOA/BIG											*/
/*					P.O. Box 127										*/
/*					CH-1015 Lausanne									*/
/*					Switzerland											*/
/* Telephone		+41(21)693.51.89									*/
/* Telefax			+41(21)693.37.01									*/
/* Email			philippe.thevenaz@epfl.ch							*/
/*																		*/
/************************************************************************/

/************************************************************************/
/* Public implementation follows										*/
/************************************************************************/

/*--- Defines ----------------------------------------------------------*/

#undef				FALSE
#define				FALSE			((int)(0 != 0))

#undef				TRUE
#define				TRUE			((int)(!FALSE))

#undef				ERROR
#define				ERROR			((int)TRUE)

/*--- Types ------------------------------------------------------------*/

struct	trsfStruct {
  double			dx[3];
  double			skew[3][3];
};

/*--- Functions --------------------------------------------------------*/

extern	int			affineTransform	(double				transform[][4],
									 double				origin[],
									 float				*inPtr,
									 float				*outPtr,
									 long				nx,
									 long				ny,
									 long				nz,
									 int				interpolationDegree,
									 float				background);

/************************************************************************/
/* Externals															*/
/*----------------------------------------------------------------------*/
/* access.c																*/
/************************************************************************/

/* access.c */
extern	void		errorReport		(char				*errorMessage);
