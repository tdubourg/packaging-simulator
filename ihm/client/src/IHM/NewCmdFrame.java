package IHM;

import client.Command;
import java.awt.Color;
import javax.swing.JFrame;

/**
 * This class allows the user to make a new order to the server : I want X
 * pallets of type A and Y of type B...
 */
public class NewCmdFrame extends javax.swing.JFrame
{

	ManagementFrame management;
	private Command threadCmd;
	int palAWarehouse;
	int palBWarehouse;

	/**
	 * Sets the number of pallets A available
	 *
	 * @param palAWarehouse number of pallets available
	 */
	public void setPalAWarehouse(int palAWarehouse)
	{
		this.palAWarehouse = palAWarehouse;
		this.productsALabel.setText("Produits A : " + palAWarehouse);
	}

	/**
	 * Sets the number of pallets B available
	 *
	 * @param palBWarehouse number of pallets available
	 */
	public void setPalBWarehouse(int palBWarehouse)
	{
		this.palBWarehouse = palBWarehouse;
		this.productsBLabel.setText("Produits B : " + palBWarehouse);
	}

	/**
	 * Creates new form NewCmdFrame
	 */
	public NewCmdFrame(ManagementFrame management, Command threadCmd)
	{
		initComponents();
		aErrorLabel.setForeground(Color.red);
		aErrorLabel.setVisible(false);
		bErrorLabel.setForeground(Color.red);
		bErrorLabel.setVisible(false);
		this.management = management;
		this.threadCmd = threadCmd;
		productsALabel.setText("Produits A : " + management.getPalAWarehouse());
		productsBLabel.setText("Produits B : " + management.getPalBWarehouse());

		if (management.getOnProduction() == false)
		{
			backButton.setText("Retour");
		}
	}

	/**
	 * This method is called from within the constructor to initialize the form.
	 * WARNING: Do NOT modify this code. The content of this method is always
	 * regenerated by the Form Editor.
	 */
	@SuppressWarnings("unchecked")
	// <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
	private void initComponents() {

		descriptionLabel = new javax.swing.JLabel();
		aLabel = new javax.swing.JLabel();
		bLabel = new javax.swing.JLabel();
		validationButton = new javax.swing.JButton();
		backButton = new javax.swing.JButton();
		aErrorLabel = new javax.swing.JLabel();
		bErrorLabel = new javax.swing.JLabel();
		aTextField = new javax.swing.JTextField();
		bTextField = new javax.swing.JTextField();
		currentWarehouseLabel = new javax.swing.JLabel();
		productsALabel = new javax.swing.JLabel();
		productsBLabel = new javax.swing.JLabel();
		stateLabel = new javax.swing.JLabel();

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Nouvelle commande");
		setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
		setResizable(false);

		descriptionLabel.setText("Veuillez spécifier le nombre de palettes commandées :");

		aLabel.setText("Palettes de produits A :");

		bLabel.setText("Palettes de produits B :");

		validationButton.setText("Valider");
		validationButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				validationButtonActionPerformed(evt);
			}
		});

		backButton.setText("Retour");
		backButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				backButtonActionPerformed(evt);
			}
		});

		aErrorLabel.setText("Produits indisponibles");

		bErrorLabel.setText("Produits indisponibles");

		aTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				aTextFieldActionPerformed(evt);
			}
		});

		bTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				bTextFieldActionPerformed(evt);
			}
		});

		currentWarehouseLabel.setText("Etat actuel du stock :");

		productsALabel.setText("Produits A");

		productsBLabel.setText("Produits B");

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addContainerGap()
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addComponent(stateLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
					.addGroup(layout.createSequentialGroup()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
							.addComponent(currentWarehouseLabel)
							.addGroup(layout.createSequentialGroup()
								.addGap(10, 10, 10)
								.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
									.addGroup(layout.createSequentialGroup()
										.addComponent(aLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addComponent(aTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
										.addComponent(aErrorLabel))
									.addComponent(productsBLabel)
									.addComponent(productsALabel)
									.addGroup(layout.createSequentialGroup()
										.addComponent(bLabel)
										.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
										.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
											.addGroup(layout.createSequentialGroup()
												.addComponent(validationButton)
												.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
												.addComponent(backButton))
											.addGroup(layout.createSequentialGroup()
												.addComponent(bTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)
												.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
												.addComponent(bErrorLabel))))))
							.addComponent(descriptionLabel))
						.addGap(0, 139, Short.MAX_VALUE)))
				.addContainerGap())
		);
		layout.setVerticalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addGap(6, 6, 6)
				.addComponent(currentWarehouseLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addComponent(productsALabel)
				.addGap(11, 11, 11)
				.addComponent(productsBLabel)
				.addGap(18, 18, 18)
				.addComponent(descriptionLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 20, Short.MAX_VALUE)
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
					.addComponent(aTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(aErrorLabel)
					.addComponent(aLabel))
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addComponent(bLabel)
					.addGroup(layout.createSequentialGroup()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
							.addComponent(bTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
							.addComponent(bErrorLabel))
						.addGap(18, 18, 18)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
							.addComponent(validationButton)
							.addComponent(backButton))))
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addComponent(stateLabel)
				.addGap(20, 20, 20))
		);

		pack();
	}// </editor-fold>//GEN-END:initComponents

	private void clearTextFields()
	{
		aTextField.setText("");
		bTextField.setText("");
	}
	GameOverPopup goPopup;

	public void setGoPopup(GameOverPopup p)
	{
		goPopup = p;
	}

	/**
	 * Close the frame after clicking on cancel button
	 *
	 * @param evt click on button "annuler"
	 */
	private void backButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_backButtonActionPerformed
		clearTextFields();
		stateLabel.setVisible(false);
		if (management.getOnProduction() == true)
		{
			this.management.setVisible(true);
		}
		else
		{
			this.goPopup.setVisible(true);
		}
		this.setVisible(false);
	}//GEN-LAST:event_backButtonActionPerformed

	/**
	 * Check if data is correct and send information to the socket after
	 * validation of new command
	 *
	 * @param evt click on button "valider"
	 */
	private void validationButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_validationButtonActionPerformed
		Boolean correct = true;
		Boolean available = true;
		int nbA;
		int nbB;

		//if nothing is the TextField, puts 0 in it
		if (aTextField.getText().isEmpty())
		{
			aTextField.setText("0");
		}

		if (bTextField.getText().isEmpty())
		{
			bTextField.setText("0");
		}

		//checks if data is correct
		try
		{
			nbA = Integer.parseInt(aTextField.getText());
		}
		catch (NumberFormatException e)
		{
			aErrorLabel.setVisible(true);
			aErrorLabel.setText("Donnée invalide");
			correct = false;
		}

		try
		{
			nbB = Integer.parseInt(bTextField.getText());
		}
		catch (NumberFormatException e)
		{
			correct = false;
			bErrorLabel.setText("Donnée invalide");
			bErrorLabel.setVisible(true);
		}

		//if data correct
		if (correct == true)
		{
			nbA = Integer.parseInt(aTextField.getText());
			nbB = Integer.parseInt(bTextField.getText());

			//checks if pallets are available in the warehouse
			if (nbA > palAWarehouse)
			{
				available = false;
				aErrorLabel.setText("Disponibilité : " + palAWarehouse);
				aErrorLabel.setVisible(true);
			}
			else
			{
				aErrorLabel.setVisible(false);
			}
			if (nbB > palBWarehouse)
			{
				available = false;
				bErrorLabel.setText("Disponibilité : " + palBWarehouse);
				bErrorLabel.setVisible(true);
			}
			else
			{
				bErrorLabel.setVisible(false);
			}

			//if available, send the data to server
			if (available == true)
			{
				// Clear text fields
				clearTextFields();

				//send data to server
				threadCmd.sendCommand(nbA, nbB);

				//close frame
				if (management.getOnProduction() == true)
				{
					this.setVisible(false);
				}
				else
				{
					// Refersh labels
					setPalAWarehouse(palAWarehouse - nbA);
					setPalBWarehouse(palBWarehouse - nbB);
					// Display confirmation :
					stateLabel.setText("Commande validée. Pour pouvez en saisir une nouvelle.");
					stateLabel.setVisible(true);
				}
			}
		}
	}//GEN-LAST:event_validationButtonActionPerformed

	private void aTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_aTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_aTextFieldActionPerformed

	private void bTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_bTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_bTextFieldActionPerformed
	// Variables declaration - do not modify//GEN-BEGIN:variables
	private javax.swing.JLabel aErrorLabel;
	private javax.swing.JLabel aLabel;
	private javax.swing.JTextField aTextField;
	private javax.swing.JLabel bErrorLabel;
	private javax.swing.JLabel bLabel;
	private javax.swing.JTextField bTextField;
	private javax.swing.JButton backButton;
	private javax.swing.JLabel currentWarehouseLabel;
	private javax.swing.JLabel descriptionLabel;
	private javax.swing.JLabel productsALabel;
	private javax.swing.JLabel productsBLabel;
	private javax.swing.JLabel stateLabel;
	private javax.swing.JButton validationButton;
	// End of variables declaration//GEN-END:variables
}
