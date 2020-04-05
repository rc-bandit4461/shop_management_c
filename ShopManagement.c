#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Client
{
    int code;
    char *firstname;
    char *lastname;
    char *telephone;
} Client;
typedef struct ClientElement
{
    Client *client;
    struct ClientElement *next;
} ClientElement;
typedef struct product
{
    int code;
    char *designation;
    double price;
    double purchasePrice;

} Product;
typedef struct ProductElement
{
    Product *product;
    struct ProductElement *next;
} ProductElement;

typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct item
{
    int quantity;
    double subTotal;
    Product *product;
} Item;
typedef struct ItemElement
{
    Item *item;
    struct ItemElement *next;
} ItemElement;
struct paymentElement;
typedef struct sale
{
    int saleCode;
    double total;
    Date date;
    ItemElement *itemsList;
    Client *client;
    struct paymentElement *paymentsList;
} Sale;
typedef struct SaleElement
{
    Sale *sale;
    struct SaleElement *next;
} SaleElement;
typedef struct payment
{
    int paymentCode;
    double amount;
    char *type;
    Date date;
    Sale *sale;
} Payment;
typedef struct paymentElement
{
    Payment *payment;
    struct paymentElement *next;
} PaymentElement;
//INPUT DATE
void inputDate(Date *date) // saisie de données d'une date
{
    do
    {
        printf("Input day : ");
        scanf("%d", &(date->day));
    } while (date->day > 31 || date->day < 1);
    do
    {
        printf("Input month : ");
        scanf("%d", &(date->month));
    } while (date->month > 12 || date->month < 1);
    do
    {
        printf("Input year : ");
        scanf("%d", &(date->year));
    } while (date->year < 1900);
}
//END_INPUT_DATE
//CLIENT_FUNCS
Client *createClient(int code, char *firstname, char *lastname, char *telephone)
{
    Client *client;
    client = (Client *)malloc(sizeof(Client));
    client->code = code;
    client->firstname = firstname;
    client->lastname = lastname;
    client->telephone = telephone;

    return client;
}

ClientElement *createElement(Client *client)
{
    ClientElement *nouv;
    nouv = (ClientElement *)malloc(sizeof(ClientElement));
    nouv->next = NULL;
    nouv->client = client;
    return nouv;
}
Client *getClient(ClientElement *ClientsList, int code)
{
    if (ClientsList == NULL)
        return NULL;
    if (ClientsList->client->code == code)
        return ClientsList->client;
    return getClient(ClientsList->next, code);
}

void addClientToList(ClientElement **ClientsList, Client *client)
{

    ClientElement *nouv;
    nouv = createElement(client);
    if (*ClientsList == NULL)
    {

        *ClientsList = nouv;
        return;
    }
    ClientElement *t = *ClientsList;
    while (t->next != NULL)
        t = t->next;
    t->next = nouv;
}
void displayClient(Client *client)
{
    if (!client)
        return;
    printf("code: %d \n", client->code);
    printf("firstname: %s\n", client->firstname);
    printf("lastname: %s\n", client->lastname);
    printf("telephone: %s\n", client->telephone);
}
void modifyClient(Client *client, int newcode, char *newfirstname, char *newlastname, char *newtelephone)
{
    if (client)
    {
        client->code = newcode;
        client->firstname = newfirstname;
        client->lastname = newlastname;
        client->telephone = newtelephone;
    }
}
void modifyProduct(Product *product, int code, double price, double purshasePrice, char *designation)
{
    if (product)
    {
        product->code = code;
        product->price = price;
        product->purchasePrice = purshasePrice;
        product->designation = designation;
    }
}
void diplayClientsList(ClientElement *L)
{
    printf("\n-----> Printing Clients List  <-----\n");
    for (; L; L = L->next)
    {
        displayClient(L->client);
        printf("-------------------\n");
    }
    printf("----->      printing ends     <-----\n");
}
void deleteClientElement(ClientElement **ClientsList, Client *client)
{
    if (*ClientsList == NULL)
        return;
    ClientElement *t = *ClientsList, *tmp;
    if (t->client == client)
    {
        *ClientsList = t->next;
        free(t->client);
        free(t);
        return;
    }
    while (t->next && t->next->client != client)
        t = t->next;
    if (t->next)
    {
        tmp = t->next;
        t->next = tmp->next;
        free(tmp->client);
        free(tmp);
    }
}
//END_CLIENT_FUNCS

//PRODUCT_FUNCS
Product *createProduct(int code, char *designation, double price, double purshasePrice)
{
    Product *product;
    product = (Product *)malloc(sizeof(Product));

    product->code = code;
    product->designation = designation;
    product->price = price;
    product->purchasePrice = purshasePrice;

    return product;
}
ProductElement *createProductElement(Product *Product)
{
    ProductElement *nouv;
    nouv = (ProductElement *)malloc(sizeof(ProductElement));
    nouv->next = NULL;
    nouv->product = Product;
    return nouv;
}
Product *getProduct(ProductElement *productsList, int code)
{
    if (productsList == NULL)
        return NULL;
    if (productsList->product->code == code)
        return productsList->product;
    return getProduct(productsList->next, code);
}

void addProductToList(ProductElement **productsList, Product *product)
{

    ProductElement *nouv;
    nouv = createProductElement(product);
    if (*productsList == NULL)
    {

        *productsList = nouv;
        return;
    }
    ProductElement *t = *productsList;
    while (t->next != NULL)
        t = t->next;
    t->next = nouv;
}
void displayProduct(Product *product)
{
    if (!product)
        return;
    printf("code: %d \n", product->code);
    printf("designation: %s\n", product->designation);
    printf("price: %.2lf\n", product->price);
    printf("purchasePrice: %.2lf\n", product->purchasePrice);
}
void diplayProductsList(ProductElement *L)
{
    printf("\n-----> Printing products List <-----\n");
    for (; L; L = L->next)
    {
        displayProduct(L->product);
        printf("-------------------\n");
    }
    printf("----->      printing ends     <-----\n");
}
void deleteProductElement(ProductElement **productsList, Product *product)
{
    if (*productsList == NULL)
        return;
    ProductElement *t = *productsList, *tmp;
    if (t->product == product)
    {
        *productsList = t->next;
        free(t->product);
        free(t);
        return;
    }
    while (t->next && t->next->product != product)
        t = t->next;
    if (t->next)
    {
        tmp = t->next;
        t->next = tmp->next;
        free(tmp->product);
        free(tmp);
    }
}

//END_PRODUCT_FUNCS

//ITEM_FUNCS
Item *createItem(Product *product, int quantity)
{
    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->product = product;
    newItem->quantity = quantity;
    newItem->subTotal = product->price * quantity;
    return newItem;
}
ItemElement *createItemElement(Item *item)
{
    ItemElement *nouv;
    nouv = (ItemElement *)malloc(sizeof(ItemElement));
    nouv->next = NULL;
    nouv->item = item;
    return nouv;
}
Item *getItem(ItemElement *itemsList, Product *product)
{
    if (itemsList == NULL)
        return NULL;
    if (itemsList->item->product == product)
        return itemsList->item;
    return getItem(itemsList->next, product);
}
void addItemToList(ItemElement **itemsList, Item *item)
{
    Item *SimilarItem = getItem(*itemsList, item->product);
    if (SimilarItem)
    {
        SimilarItem->quantity += item->quantity;
        SimilarItem->subTotal += item->quantity * item->product->price;
        free(item);
        return;
    }
    ItemElement *nouv;
    nouv = createItemElement(item);
    nouv->next = *itemsList;
    *itemsList = nouv;
}
void DeleteItemElement(ItemElement **itemsList, Product *product)
{
    if (*itemsList == NULL)
        return;
    ItemElement *t = *itemsList, *tmp;
    if (t->item->product == product)
    {

        *itemsList = t->next;
        free(t->item); //liberation espace de Item
        free(t);       //Liberation espace de ItemElement
        return;
    }
    while (t->next && t->next->item->product != product)
        t = t->next;
    if (t->next)
    {
        tmp = t->next;
        t->next = tmp->next;
        free(tmp->item);
        free(tmp);
    }
}
void deleteAllItems(ItemElement *itemsList) //Utilis?e lors de suppression d'une vente
{
    if (itemsList)
    {
        deleteAllItems(itemsList->next);
        free(itemsList->item);
        free(itemsList);
    }
}

void displayItem(Item *item)
{
    if (!item)
        return;
    printf("Product : %d\n", item->product->code);
    printf("Price : %.2f\n", item->product->price);
    printf("quantity : %d\n", item->quantity);
    printf("Subtotal : %.2lf\n", item->subTotal);
}
void displayItemsList(ItemElement *itemsList)
{
    printf("\n-------- items List --------\n");
    while (itemsList)
    {
        printf("-->Item  :  \n");
        displayItem(itemsList->item);
        itemsList = itemsList->next;
    }
    printf("\n----------------------------\n");
}
//END_ITEM_FUNCS

//PAYMENT_FUNCS
Payment *createPayment(int paymentCode, double amount, char *type, Date date, Sale *sale)
{
    Payment *payment;
    payment = (Payment *)malloc(sizeof(Payment));
    payment->paymentCode = paymentCode;
    payment->type = type;
    payment->date = date;
    payment->sale = sale;
    payment->amount = amount;

    return payment;
}
PaymentElement *createPaymentElement(Payment *payment)
{
    PaymentElement *nouv;
    nouv = (PaymentElement *)malloc(sizeof(PaymentElement));
    nouv->next = NULL;
    nouv->payment = payment;
    return nouv;
}
Payment *getPayment(PaymentElement *paymentsList, int paymentCode)
{
    if (paymentsList == NULL)
        return NULL;
    if (paymentsList->payment->paymentCode == paymentCode)
        return paymentsList->payment;
    return getPayment(paymentsList->next, paymentCode);
}
void addPaymentToList(PaymentElement **paymentsList, Payment *payment)
{
    if (getPayment(*paymentsList, payment->paymentCode))
    {
        printf("This payment code is already in use.\n");
        return;
    }
    PaymentElement *nouv;
    nouv = createPaymentElement(payment);
    nouv->next = *paymentsList;
    *paymentsList = nouv;
}

void displayPayment(Payment *payment)
{
    if (!payment)
        return;
    printf("paymentCode: %d \n", payment->paymentCode);
    printf("type: %s\n", payment->type);
    printf("Date: %d/%d/%d \n", payment->date.day, payment->date.month, payment->date.year);
    printf("amount: %.2lf\n", payment->amount);
    printf("Sale code: %d\n", payment->sale->saleCode);
}
void displayPaymentsList(PaymentElement *L)
{
    printf("\n-----> Printing Payments List  <-----\n");
    for (; L; L = L->next)
    {
        displayPayment(L->payment);
        printf("-------------------\n");
    }
    printf("----->      printing ends     <-----\n");
}
void deletePayment(PaymentElement **PaymentsList, int paymentCode)
{
    if (*PaymentsList == NULL)
        return;
    PaymentElement *t = *PaymentsList, *tmp;
    if (t->payment->paymentCode == paymentCode)
    {
        *PaymentsList = t->next;
        free(t->payment);
        free(t);
        return;
    }
    while (t->next && t->next->payment->paymentCode != paymentCode)
        t = t->next;
    if (t->next)
    {
        tmp = t->next;
        t->next = tmp->next;
        free(tmp->payment);
        free(tmp);
    }
}
void modifyPayment(Payment *payment, int paymentCode, double amount, char *paymentType, Date date)
{
    if (!payment)
        return;
    payment->date = date;
    payment->paymentCode = paymentCode;
    payment->amount = amount;
}
void deleteAllPayments(PaymentElement *paymentElement) //utilis?e en cas de suppression d'une vente
{
    if (paymentElement)
    {
        deleteAllPayments(paymentElement->next);
        free(paymentElement->payment);
        free(paymentElement);
    }
}
//PAYMENT_FUNCS

//INPUT_FUNCS
void InputSaleInfo(int *saleCode, int *clientCode, Date *date) //saisie des données
{
    printf("\n-------> input Sale info <-------\n");
    printf("saleCode : ");
    scanf("%d", saleCode);
    printf("clientCode : ");
    scanf("%d", clientCode);
    inputDate(date);
    printf("------->     input ends     <-------\n");
}
void InputIntemInfo(int *productCode, int *quantity)
{
    printf("productCode : ");
    scanf("%d", productCode);
    do
    {
        printf("quantity : ");
        scanf("%d", quantity);
    } while (*quantity < 1);
}
void InputInfoPayment(int *paymentCode, double *amount, char **type, Date *date)
{
    printf("\n-------> input payment  info <-------\n");
    char tmp[50];
    printf("input paymentCode : ");
    scanf("%d", paymentCode);
    fflush(stdin);
    printf("input type : ");
    scanf("%s", tmp);

    *type = (char *)malloc(strlen(tmp) + 1);
    strcpy(*type, tmp);
    inputDate(date);
    do
    {
        printf("input amount : ");
        scanf("%lf", amount);
    } while (*amount <= 0);

    //normalement, la date du paiment doit etre sup?rieur ou ?gal ? la date du vente
    printf("------->  input payment ends <-------\n");
}
void InputInfoClient(int *code, char **firstname, char **lastname, char **telephone)
{
    printf("\n-------> input client  info <-------\n");
    char tmp[50];
    printf("code : ");
    scanf("%d", code);
    fflush(stdin);
    printf("firstname : ");
    scanf("%s", tmp);
    *firstname = (char *)malloc(strlen(tmp) + 1);
    strcpy(*firstname, tmp);
    fflush(stdin);
    printf("lastname : ");
    scanf("%s", tmp);
    *lastname = (char *)malloc(strlen(tmp) + 1);
    strcpy(*lastname, tmp);
    fflush(stdin);
    printf("telephone : ");
    scanf("%s", tmp);
    *telephone = (char *)malloc(strlen(tmp) + 1);
    strcpy(*telephone, tmp);
    printf("------->     input ends     <-------\n");
}
void inputProductInfo(int *code, double *price, double *purshasePrice, char **designation) //saisie des donnÃ©es
{
    printf("\n-------> input product info <-------\n");
    char tmp[50];
    printf("code : ");
    scanf("%d", code);
    printf("Price : ");
    scanf("%lf", price);
    printf("PurshacePrice  : ");
    scanf("%lf", purshasePrice);
    printf("designation : ");
    fflush(stdin);
    gets(tmp);
    *designation = (char *)malloc(strlen(tmp) + 1);
    strcpy(*designation, tmp);
    printf("------->     input ends     <-------\n");
}
//END_INPUT_FUNCS

//SALE_FUNCS
Sale *createSale(int saleCode, Date date, Client *client)
{
    Sale *newSale = (Sale *)malloc(sizeof(Sale));
    newSale->saleCode = saleCode;
    newSale->client = client;
    newSale->date = date;
    newSale->paymentsList = NULL;
    newSale->itemsList = NULL;
    return newSale;
}
SaleElement *createSaleElement(Sale *sale)
{
    SaleElement *nouv;
    nouv = (SaleElement *)malloc(sizeof(SaleElement));
    nouv->next = NULL;

    nouv->sale = sale;
    return nouv;
}
Sale *getSale(SaleElement *salesList, int saleCode)
{
    if (salesList == NULL)
        return NULL;
    if (salesList->sale->saleCode == saleCode)
        return salesList->sale;
    return getSale(salesList->next, saleCode);
}
void addItemElementtoSale(Sale *sale, Product *product, int quantity)
{
    Item *item = createItem(product, quantity);
    addItemToList(&sale->itemsList, item);
}
void modifyItemQuantitySale(Sale *sale, Product *product, int quantity) //modifier la quantit?
                                                                        //d'un Item donn?e
{
    if (!sale)
        return;
    Item *item = getItem(sale->itemsList, product);
    if (item)
    {
        item->subTotal = product->price * quantity;
        if (quantity < item->quantity)
            sale->total -= product->price * (item->quantity - quantity);
        else
            sale->total += product->price * (quantity - item->quantity);
        item->quantity = quantity;
        if (quantity == 0)
            DeleteItemElement(&sale->itemsList, product);
    }
    else
    {
        printf("This product is not in the items list\n");
    }
}
void addSaleToList(SaleElement **salesList, Sale *sale)
{
    SaleElement *nouv;
    nouv = createSaleElement(sale);
    nouv->next = *salesList;
    *salesList = nouv;
}
void DeleteSaleElement(SaleElement **salesList, Sale *sale)
{
    if (*salesList == NULL)
        return;
    SaleElement *t = *salesList, *tmp;
    if (t->sale == sale)
    {

        *salesList = t->next;
        deleteAllItems(t->sale->itemsList); //suppressions de toutes les lignes de commandes
        free(t->sale);                      //liberation espace de Sale
        free(t);                            //Liberation espace de SaleElement
        return;
    }
    while (t->next && t->next->sale != sale)
        t = t->next;
    if (t->next)
    {
        tmp = t->next;
        t->next = tmp->next;
        deleteAllItems(tmp->sale->itemsList); //suppressions de toutes les lignes de commandes
        free(tmp->sale);                      //liberation espace de Sale
        free(tmp);                            //Liberation espace de SaleElement
    }
}
void UpdateSales(SaleElement *salesList)
{                   // mise ? jour des subtotals et totals en cas de modification de prix
    ItemElement *t; // d'un produit
    double total;
    while (salesList)
    {
        total = 0;
        t = salesList->sale->itemsList;
        while (t)
        {
            t->item->subTotal = t->item->product->price * t->item->quantity;
            total += t->item->subTotal;
            t = t->next;
        }
        salesList->sale->total = total;
        salesList = salesList->next;
    }
}
double calculateSaleTotal(Sale *sale)
{
    if (!sale)
        return -1;
    double total = 0;
    ItemElement *t = sale->itemsList;
    while (t)
    {
        total += t->item->subTotal;
        t = t->next;
    }
    return total;
}
void displaySale(Sale *sale)
{
    if (!sale)
        return;
    printf("SaleCode : %d\n", sale->saleCode);
    printf("ClientNo : %d\n", sale->client->code);
    printf("Date and time of purshase : %d/%d/%d  \n", sale->date.day, sale->date.month, sale->date.year);
    displayItemsList(sale->itemsList);
    printf("Total : %.2f\n", sale->total);
}
void displaySalesList(SaleElement *salesList)
{
    printf("----> Displaying sales list <----");
    while (salesList)
    {
        printf("-----\n");
        displaySale(salesList->sale);
        salesList = salesList->next;
    }
    printf("---------------------------------\n");
}

void ItemsAddingMenu(Sale *sale, ProductElement *productsList)
{
    int productCode, quantity;
    Product *product;
    int choice;
RMI:
    printf("Sale Items menu :  \n");
    printf("1-> Add Item \n");
    printf("2-> Delete Item \n");
    printf("3-> Exit \n");
    printf("choose : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        InputIntemInfo(&productCode, &quantity);
        product = getProduct(productsList, productCode);
        if (!product)
        {
            printf("this product code does not exist.\n");
            break;
        }
        addItemToList(&sale->itemsList, createItem(product, quantity));
        break;
    case 2:
        printf("input the product code : ");
        scanf("%d", &productCode);
        product = getProduct(productsList, productCode);
        if (!product)
        {
            printf("this product code does not exist.\n");
            break;
        }
        DeleteItemElement(&sale->itemsList, product);
        break;
    case 3:
        return;
        break;
    }
    goto RMI;
}
//END_SALE_FUNCS
//MENUS
void EditSaleMenu(Sale *sale, ClientElement *clientsList, ProductElement *productsList)
{
    if (sale)
    {
        Client *client;
        Product *product;
        Payment *payment;
        char tmp[50];
        int code, choice, quantity, paymentCode;
        double amount;
        char *paymentType;
        char c;

        Date date;
    MSM:
        printf("Sale Editing menu : \n");
        printf("1-> print Sale \n");
        printf("2-> print payments \n");
        printf("3-> add payment \n");
        printf("4-> modify Payment \n");
        printf("5-> delete Payment \n");
        printf("6-> modify client \n");
        printf("7-> modify date \n");
        printf("8-> modify quantity Item \n");
        printf("9-> Delete Item \n");
        printf("10-> Exit \n");
        printf("choisir choix : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displaySale(sale);
            break;
        case 2:
            displayPaymentsList(sale->paymentsList);
            break;
        case 3:
            InputInfoPayment(&paymentCode, &amount, &paymentType, &date);
            addPaymentToList(&sale->paymentsList, createPayment(paymentCode, amount, paymentType, date, sale));
            break;
        case 4:
            printf("input payment code : \n");
            scanf("%d", &code);
            payment = getPayment(sale->paymentsList, code);
            if (!payment)
            {
                printf("this payment code does not exist.\n");
                break;
            }
            paymentCode = payment->paymentCode;
            date = payment->date;
            paymentType = payment->type;
            amount = payment->amount;

            printf("change paymentCode ? (y/n)");
            fflush(stdin);
            scanf("%s", &c);
            if (c == 'y' || c == 'Y')
            {
                printf("input new paymentCode :");
                scanf("%d", &paymentCode);
                if (getPayment(sale->paymentsList, paymentCode) && paymentCode != payment->paymentCode)
                {
                    printf("this PaymentCode is already used.\n");
                    paymentCode = payment->paymentCode;
                }
            }
            printf("change amount ? (y/n)");
            fflush(stdin);
            scanf("%s", &c);
            if (c == 'y' || c == 'Y')
            {
                printf("input new amount :");
                scanf("%lf", &amount);
            }
            printf("change date ? (y/n)");
            fflush(stdin);
            scanf("%s", &c);
            if (c == 'y' || c == 'Y')
            {
                printf("input new date :\n");
                inputDate(&date);
            }
            printf("change type ? (y/n)");
            fflush(stdin);
            scanf("%s", &c);
            if (c == 'y' || c == 'Y')
            {
                printf("input new paymentType  :");
                fflush(stdin);
                scanf("%[^\n]s", tmp);
                paymentType = (char *)malloc(strlen(tmp) + 1);
                strcpy(paymentType, tmp);
            }
            modifyPayment(payment, paymentCode, amount, paymentType, date);
            break;
        case 5:
            printf("input payment code : \n");
            scanf("%d", &code);
            deletePayment(&sale->paymentsList, code);
            break;
        case 6:
            printf("Input client code : \n");
            scanf("%d", &code);
            client = getClient(clientsList, code);
            if (client)
                sale->client = client;
            else
                printf("This client code does not exist.\n");
            break;
        case 7:
            inputDate(&date);
            sale->date = date;
            ;
            break;
        case 8:
            printf("input the product code : \n");
            scanf("%d", &code);
            do
            {
                printf("Input the quantity : \n");
                scanf("%d", &quantity);
            } while (quantity < 0);
            product = getProduct(productsList, code);
            if (!product)
            {
                printf("This product code does not exist.\n");
                break;
            }
            modifyItemQuantitySale(sale, product, quantity);
            break;
        case 9:
            printf("input the product code : \n");
            scanf("%d", &code);
            product = getProduct(productsList, code);
            if (product)
                DeleteItemElement(&sale->itemsList, product);
            else
                printf("This product code does not exist.\n");
            break;
        case 10:
            return;
            break;
        }
        goto MSM;
    }
}
void SaleMenu(SaleElement **salesList, ClientElement *clientsList, ProductElement *productsList)
{
    int clientCode, productCode, quantity, saleCode, paymentCode;
    Product *product;
    double amount;
    Client *client;
    Sale *sale;
    char *paymentType;
    Payment *payment;
    int choice;
    char paymentchoice;
    Date date;

RMS:
    printf("Sales Menu  : \n");
    printf("1-> Add Sale \n");
    printf("2-> Edit/View Sale \n");
    printf("3-> Delete a Sale \n");
    printf("4-> Print a Sale \n");
    printf("5-> Print Sales List \n");
    printf("6-> Update sales total and subtotal amounts \n");
    printf("7-> Exit \n");
    printf("choose : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        InputSaleInfo(&saleCode, &clientCode, &date);
        sale = getSale(*salesList, saleCode);
        if (sale)
        {
            printf("this sale code is already in use.\n");
            break;
        }
        client = getClient(clientsList, clientCode);
        if (client == NULL)
        {
            printf("this client code does not exist.\n");
            break;
        }
        sale = createSale(saleCode, date, client);
        addSaleToList(salesList, sale);
        ItemsAddingMenu(sale, productsList);
        if (sale->itemsList == NULL)
        {
            printf("This sale has no items.\n");
            DeleteSaleElement(salesList, sale);
            break;
        }
        do
        {
            printf("add payment ? (y/n) :");
            fflush(stdin);
            scanf("%s", &paymentchoice);
            if (paymentchoice != 'Y' && paymentchoice != 'y')
                break;
            InputInfoPayment(&paymentCode, &amount, &paymentType, &date);
            addPaymentToList(&sale->paymentsList, createPayment(paymentCode, amount, paymentType, date, sale));

        } while (paymentchoice == 'y' || paymentchoice == 'Y');
        sale->total = calculateSaleTotal(sale);

        break;
    case 2:
        printf("input the code of the Sale : ");
        scanf("%d", &saleCode);
        sale = getSale(*salesList, saleCode);
        if (!sale)
        {
            printf("This salecode does not exist.\n");
            break;
        }

        EditSaleMenu(sale, clientsList, productsList);
        if (sale->itemsList == NULL)
        {
            DeleteSaleElement(salesList, sale);
        }
        break;
    case 3:
        printf("input the code of the Sale : ");
        scanf("%d", &saleCode);
        sale = getSale(*salesList, saleCode);
        if (!sale)
        {
            printf("This Sale code does not exist.\n");
            break;
        }
        DeleteSaleElement(salesList, sale);
        break;
    case 4:
        printf("input the code of the Sale : ");
        scanf("%d", &saleCode);

        sale = getSale(*salesList, saleCode);
        if (!sale)
        {
            printf("This Sale code does not exist.\n");
        }
        else
        {
            printf("Princting Sale info -----\n");
            displaySale(sale);
            printf("---------------------------\n");
        }
        break;
    case 5:
        displaySalesList(*salesList);
        break;
    case 6:
        UpdateSales(*salesList);
    case 7:
        return;
        break;
    }
    goto RMS;
}
void clientMenu(ClientElement **clientsList, SaleElement **salesList)
{
    int code;
    Client *client;
    int choice;
    SaleElement *t, *q;
    char *firstname, *lastname, *telephone;
RMC:
    printf("Clients Menu : \n");
    printf("1-> Add client \n");
    printf("2-> modify client \n");
    printf("3-> Delete client \n");
    printf("4-> print client \n");
    printf("5-> print clients list \n");
    printf("6-> Exit \n");
    printf(" Choose : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        InputInfoClient(&code, &firstname, &lastname, &telephone);
        if (getClient(*clientsList, code))
        {
            printf("This client code does not exist.\n");
            break;
        }
        addClientToList(clientsList, createClient(code, firstname, lastname, telephone));
        break;
    case 2:
        printf("input the code of the client : ");
        scanf("%d", &code);
        client = getClient(*clientsList, code);
        if (!client)
        {
            printf("this client code does not exist.\n");
            break;
        }
        printf("\n---> Input new client info : \n");
        InputInfoClient(&code, &firstname, &lastname, &telephone);
        if (code != client->code && getClient(*clientsList, code))
        {
            printf("This client code is already used.\n");
            break;
        }
        modifyClient(client, code, firstname, lastname, telephone);
        break;
    case 3:
        printf("input the code of the client : ");
        scanf("%d", &code);
        client = getClient(*clientsList, code);
        if (client)
        {
            if (!*salesList)
            {
                deleteClientElement(clientsList, client);
                break;
            }
            q = *salesList;
            if (q->next == NULL)
            {
                if (q->sale->client == client)
                    DeleteSaleElement(salesList, q->sale);
            }
            else
            {
                for (t = q->next; t;)
                    if (t->sale->client == client)
                    {
                        deleteAllPayments(t->sale->paymentsList);
                        deleteAllItems(t->sale->itemsList);
                        q->next = t->next;
                        free(t);
                        t = q->next;
                    }
                    else
                    {
                        q = t;
                        t = t->next;
                    }
                if (q->sale->client == client)
                    DeleteSaleElement(salesList, q->sale);
            }

            deleteClientElement(clientsList, client);
        }
        else
            printf("This client code does not exist.\n");
        break;
    case 4:
        printf("input the code of the client : ");
        scanf("%d", &code);

        client = getClient(*clientsList, code);
        if (!client)
        {
            printf("This client code does not exist.\n");
        }
        else
        {
            printf("Princting client info -----\n");
            displayClient(client);
            printf("---------------------------\n");
        }
        break;
    case 5:
        diplayClientsList(*clientsList);
        break;
    case 6:
        return;
        break;
    }
    goto RMC;
}
void ProductMenu(ProductElement **productsList, SaleElement **salesList)
{
    int code;
    Product *product;
    int choice;
    double price, purshasePrice, oldPrice;
    char *designation;
    SaleElement *t, *q;
RMP:
    printf("Products Menu : \n");
    printf("1-> Add product \n");
    printf("2-> modify product \n");
    printf("3-> delete product \n");
    printf("4-> print product \n");
    printf("5-> print products list\n");
    printf("6-> Exit \n");
    printf(" Choose : ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        inputProductInfo(&code, &price, &purshasePrice, &designation);
        if (getProduct(*productsList, code))
        {
            printf("This product code is already used.\n");
            break;
        }
        addProductToList(productsList, createProduct(code, designation, price, purshasePrice));
        break;
    case 2:
        printf("input the code of the Product : ");
        scanf("%d", &code);
        product = getProduct(*productsList, code);
        if (!product)
        {
            printf("this product code does not exist.\n");
            break;
        }
        printf("\n---> Input new product info : \n");
        oldPrice = product->price;
        inputProductInfo(&code, &price, &purshasePrice, &designation);
        if (code != product->code && getProduct(*productsList, code))
        {
            printf("This product code is already used.\n");
            break;
        }
        modifyProduct(product, code, price, purshasePrice, designation);
        if (product->price != oldPrice)
            UpdateSales(*salesList);
        break;
    case 3:
        printf("input the code of the Product : ");
        scanf("%d", &code);
        printf("input the code of the product : ");
        scanf("%d", &code);
        product = getProduct(*productsList, code);
        if (product)
        {
            if (!*salesList)
            {
                deleteProductElement(productsList, product);
                break;
            }
            q = *salesList;
            if (q->next == NULL)
            {
                if (getItem(q->sale->itemsList, product))
                    DeleteItemElement(&q->sale->itemsList, product);
                if (q->sale->itemsList == NULL)
                    DeleteSaleElement(salesList, q->sale);
                else
                    q->sale->total = calculateSaleTotal(q->sale);
            }
            else
            {
                for (t = q->next; t;)
                    if (getItem(t->sale->itemsList, product))
                    {

                        DeleteItemElement(&q->sale->itemsList, product);
                        if (q->sale->itemsList == NULL)
                        {
                            q->next = t->next;
                            free(t);
                            t = q->next;
                        }
                        else
                        {
                            t->sale->total = calculateSaleTotal(t->sale);
                            q = t;
                            t = t->next;
                        }
                    }
                    else
                    {
                        q = t;
                        t = t->next;
                    }
                if (getItem(q->sale->itemsList, product))
                    DeleteItemElement(&q->sale->itemsList, product);
                if (q->sale->itemsList == NULL)
                    DeleteSaleElement(salesList, q->sale);
                else
                    q->sale->total = calculateSaleTotal(q->sale);
            }

            deleteProductElement(productsList, product);
        }

        break;
    case 4:
        printf("input the code of the Product : ");
        scanf("%d", &code);
        product = getProduct(*productsList, code);
        if (!product)
        {
            printf("This Product code does not exist.\n");
        }
        else
        {
            printf("Princting Product info -----\n");
            displayProduct(product);
            printf("---------------------------\n");
        }
        break;
    case 5:
        diplayProductsList(*productsList);
        break;
    case 6:
        return;
        break;
    }
    goto RMP;
}
int main()
{
    int code;
    double price, purshasePrice;
    char *designation;
    SaleElement *SalesList = NULL;
    ProductElement *ProductsList = NULL;
    char *firstname, *lastname, *telephone;
    ClientElement *ClientsList = NULL;
    int choice;
    // Data for direct testing
    // you can incomment the code to use it
    // 
    // code = 1;
    // price = 10;
    // purshasePrice = 5;
    // designation = (char *)malloc(sizeof(char) * 20);
    // strcpy(designation, "tonic bimo");
    // addProductToList(&ProductsList, createProduct(code, designation, price, purshasePrice));
    // code = 2;
    // price = 50;
    // purshasePrice = 20;
    // designation = (char *)malloc(sizeof(char) * 20);
    // strcpy(designation, "Tide 10kg");
    // addProductToList(&ProductsList, createProduct(code, designation, price, purshasePrice));
    // diplayProductsList(ProductsList);
    // code = 1;
    // firstname = (char *)malloc(sizeof(char) * 20);
    // strcpy(firstname, "ayman");
    // lastname = (char *)malloc(sizeof(char) * 20);
    // strcpy(lastname, "boubleh");
    // telephone = (char *)malloc(sizeof(char) * 20);
    // strcpy(telephone, "0626478495");
    // addClientToList(&ClientsList, createClient(code, firstname, lastname, telephone));
    // code = 2;
    // firstname = (char *)malloc(sizeof(char) * 20);
    // strcpy(firstname, "haitam");
    // lastname = (char *)malloc(sizeof(char) * 20);
    // strcpy(lastname, "boubleh");
    // telephone = (char *)malloc(sizeof(char) * 20);
    // strcpy(telephone, "999999999");
    // addClientToList(&ClientsList, createClient(code, firstname, lastname, telephone));
    // diplayClientsList(ClientsList);
    //
    //

    while (1)
    {
        printf("Menu  : \n");
        printf("1-> Clients \n");
        printf("2-> Products \n");
        printf("3-> Sales \n");
        printf("4-> Exit \n");
        printf("choose : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            clientMenu(&ClientsList, &SalesList);
            break;
        case 2:
            ProductMenu(&ProductsList, &SalesList);
            break;
        case 3:
            SaleMenu(&SalesList, ClientsList, ProductsList);
            break;
        case 4:
            return 0;
        }
    }
    return 0;
}
