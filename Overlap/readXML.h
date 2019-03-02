int** readXML(char* name, int* i)
{
	int **mat;
	xmlChar *id, *from, *to;
	
	int id_from, id_to, turn=0;
	int j, k;
	
	xmlDocPtr doc_ptr;
	xmlNodePtr node_ptr;
	
	doc_ptr = xmlParseFile(name);
	
	if(doc_ptr == NULL)
		printf("Deu ruim no doc negada\nAparentemente nao leu nenhum arquivo\n");
	
	node_ptr = xmlDocGetRootElement(doc_ptr);
	
	if(node_ptr == NULL)
	{
		printf("Documento vazio\n");
		xmlFreeDoc(doc_ptr);
	}
	
	if(xmlStrcmp(node_ptr->name,  (const xmlChar *) "topology"))
	{
		printf("Tipo errado de documento\n");
		xmlFreeDoc(doc_ptr);
	}
	
	node_ptr = node_ptr->xmlChildrenNode;
	while(node_ptr != NULL)
	{
		if(!(xmlStrcmp(node_ptr->name,  (const xmlChar *) "node")))
		{
			id = xmlGetProp(node_ptr, (const xmlChar *) "id");

			*i=(*i+1);
			printf("%d teste\n", *i);
		}else if(!(xmlStrcmp(node_ptr->name,  (const xmlChar *) "link")))
		{
			if(turn==0)
			{
				turn=1;
				mat= calloc(*i, sizeof(int *));
				for(j=0; j<*i; j++)
					mat[j]= calloc(*i, sizeof(int));
				
				from = xmlGetProp(node_ptr, (const xmlChar *) "from");
				to = xmlGetProp(node_ptr, (const xmlChar *) "to");
				
				id_from = atoi((char *) from);
				id_to = atoi((char *) to);
				
				mat[id_from][id_to]=1;
				mat[id_to][id_from]=1;
			}else
			{
				from = xmlGetProp(node_ptr, (const xmlChar *) "from");
				to = xmlGetProp(node_ptr, (const xmlChar *) "to");
				
				id_from = atoi((char *) from);
				id_to = atoi((char *) to);
				
				mat[id_from][id_to]=1;
				mat[id_to][id_from]=1;
			}
		}
		
		node_ptr = node_ptr->next;
	}
	
	xmlCleanupParser();
	xmlFreeNodeList(node_ptr);
	xmlFreeDoc(doc_ptr);
	node_ptr=NULL;
	doc_ptr=NULL;
	
	
	return mat;
}
