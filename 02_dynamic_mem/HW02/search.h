#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "read_product.h"

#include "read_quote.h"

#include "print_results.h"

void ReadFilesDynamically(char *productFilename, char *quoteFilename,
									product_list *wf, quote_list *qf);

void SearchForProductByRAM(int desiredRam, product_list *wf, quote_list *qf);

void SearchForProductByScreenSize(double desiredSize, product_list *wf, quote_list *qf);

#endif // SEARCH_H
