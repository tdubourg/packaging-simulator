
package IHM;

import client.Client;
import client.Command;
import client.ThreadLog;
import java.awt.Color;

public class ParametersFrame extends javax.swing.JFrame {

	Command threadCmd;
	ThreadLog threadLog;
	private final ManagementFrame managementFrame;

	/**
	 * Creates new form ManagerFrame
	 */
	public ParametersFrame(Command threadCmd, ThreadLog threadLog) {
		initComponents();
		rebusErrorLabel.setVisible(false);
		rebusErrorLabel.setForeground(Color.red);
		rebusErrorLabelLessOrEqualTo.setVisible(false);
		rebusErrorLabelLessOrEqualTo.setForeground(Color.red);
		boxErrorLabel.setVisible(false);
		boxErrorLabel.setForeground(Color.red);
		palErrorLabel.setVisible(false);
		palErrorLabel.setForeground(Color.red);
		qteErrorLabel.setVisible(false);
		qteErrorLabel.setForeground(Color.red);
		this.threadCmd = threadCmd;
		this.threadLog = threadLog;
		this.managementFrame = new ManagementFrame(this.threadCmd, this.threadLog);
		this.managementFrame.setParamsFrame(this);
	}

	/**
	 * This method is called from within the constructor to initialize the form. 
		 * WARNING: Do NOT modify this code. The content of this method is always regenerated by the Form Editor.
	 */
	// <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
	private void initComponents() {

		parametersLabel = new javax.swing.JLabel();
		panelA = new javax.swing.JPanel();
		rebusLabel = new javax.swing.JLabel();
		rebusTextField = new javax.swing.JTextField();
		boxLabel = new javax.swing.JLabel();
		boxTextField = new javax.swing.JTextField();
		palLabel = new javax.swing.JLabel();
		palTextField = new javax.swing.JTextField();
		rebusErrorLabel = new javax.swing.JLabel();
		boxErrorLabel = new javax.swing.JLabel();
		palErrorLabel = new javax.swing.JLabel();
		qteLabel = new javax.swing.JLabel();
		qteTextField = new javax.swing.JTextField();
		qteErrorLabel = new javax.swing.JLabel();
		rebusErrorLabelLessOrEqualTo = new javax.swing.JLabel();
		ValidateButton = new javax.swing.JButton();
		lotComboBox = new javax.swing.JComboBox();

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Saisie des paramètres");
		setResizable(false);

		parametersLabel.setText("Veuillez renseigner les paramètres pour le prochain lot à fabriquer");

		panelA.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));

		rebusLabel.setText("Nombre maximal de pièces défectueuses par carton :");

		rebusTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				rebusTextFieldActionPerformed(evt);
			}
		});

		boxLabel.setText("Nombre de pièces par carton :");

		boxTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				boxTextFieldActionPerformed(evt);
			}
		});

		palLabel.setText("Nombre de cartons par palette :");

		palTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				palTextFieldActionPerformed(evt);
			}
		});

		rebusErrorLabel.setText("Donnée invalide");

		boxErrorLabel.setText("Donnée invalide");

		palErrorLabel.setText("Donnée invalide");

		qteLabel.setText("Nombre de palettes à produire :");

		qteTextField.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				qteTextFieldActionPerformed(evt);
			}
		});

		qteErrorLabel.setText("Donnée invalide");

		rebusErrorLabelLessOrEqualTo.setForeground(new java.awt.Color(255, 0, 0));
		rebusErrorLabelLessOrEqualTo.setText("Doit être <= Nb Pièces par carton");

		javax.swing.GroupLayout panelALayout = new javax.swing.GroupLayout(panelA);
		panelA.setLayout(panelALayout);
		panelALayout.setHorizontalGroup(
			panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(panelALayout.createSequentialGroup()
				.addContainerGap()
				.addGroup(panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addComponent(rebusLabel)
					.addGroup(panelALayout.createSequentialGroup()
						.addComponent(rebusTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(rebusErrorLabel)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(rebusErrorLabelLessOrEqualTo))
					.addComponent(boxLabel)
					.addGroup(panelALayout.createSequentialGroup()
						.addComponent(boxTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(boxErrorLabel))
					.addComponent(palLabel)
					.addGroup(panelALayout.createSequentialGroup()
						.addComponent(palTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(palErrorLabel))
					.addComponent(qteLabel)
					.addGroup(panelALayout.createSequentialGroup()
						.addComponent(qteTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
						.addComponent(qteErrorLabel)))
				.addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
		);
		panelALayout.setVerticalGroup(
			panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(panelALayout.createSequentialGroup()
				.addContainerGap()
				.addComponent(rebusLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addGroup(panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
					.addComponent(rebusTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(rebusErrorLabel)
					.addComponent(rebusErrorLabelLessOrEqualTo))
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
				.addComponent(boxLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addGroup(panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
					.addComponent(boxTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(boxErrorLabel))
				.addGap(13, 13, 13)
				.addComponent(palLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addGroup(panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
					.addComponent(palTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(palErrorLabel))
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
				.addComponent(qteLabel)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addGroup(panelALayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
					.addComponent(qteTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
					.addComponent(qteErrorLabel))
				.addContainerGap(14, Short.MAX_VALUE))
		);

		ValidateButton.setText("Valider");
		ValidateButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				ValidateButtonActionPerformed(evt);
			}
		});

		lotComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "A", "B" }));
		lotComboBox.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				lotComboBoxActionPerformed(evt);
			}
		});

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
					.addGroup(layout.createSequentialGroup()
						.addContainerGap()
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
							.addComponent(panelA, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
							.addGroup(layout.createSequentialGroup()
								.addGap(10, 10, 10)
								.addComponent(lotComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
							.addComponent(parametersLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
					.addGroup(layout.createSequentialGroup()
						.addGap(130, 130, 130)
						.addComponent(ValidateButton)))
				.addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
		);
		layout.setVerticalGroup(
			layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
			.addGroup(layout.createSequentialGroup()
				.addComponent(parametersLabel)
				.addGap(3, 3, 3)
				.addComponent(lotComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addComponent(panelA, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
				.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
				.addComponent(ValidateButton)
				.addContainerGap())
		);

		pack();
	}// </editor-fold>//GEN-END:initComponents

	private void rebusTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_rebusTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_rebusTextFieldActionPerformed

	private void boxTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_boxTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_boxTextFieldActionPerformed

	private void palTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_palTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_palTextFieldActionPerformed

		/**
		 * saves the parameters of production if data is correct
		 * @param evt click on button "valider"
		 */
	private void ValidateButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ValidateButtonActionPerformed
		Boolean correct = true;
		rebusErrorLabel.setVisible(false);
		rebusErrorLabelLessOrEqualTo.setVisible(false);
		boxErrorLabel.setVisible(false);
		palErrorLabel.setVisible(false);
		int rebus = 0;
		int box = 0;
		int pal;
		int qte;
		String lot;

				//check if data is correct
		try {
						rebus = Integer.parseInt(rebusTextField.getText());
						if ( rebus <0 )
						{
							correct = false;
							rebusErrorLabel.setVisible(true);
						}
		} catch (NumberFormatException e) {
			correct = false;
			rebusErrorLabel.setVisible(true);
		}

		try {
			box = Integer.parseInt(boxTextField.getText());
						if ( box <0 )
						{
							correct = false;
							boxErrorLabel.setVisible(true);
						}
		} catch (NumberFormatException e) {
			correct = false;
			boxErrorLabel.setVisible(true);
		}
		
		if (rebus > box) {
			correct = false;
			rebusErrorLabelLessOrEqualTo.setVisible(true);
		}

		try {
			pal = Integer.parseInt(this.palTextField.getText());
						if ( pal <0 )
						{
							correct = false;
							palErrorLabel.setVisible(true);
						}
		} catch (NumberFormatException e) {
			correct = false;
			palErrorLabel.setVisible(true);
		}

		try {
			qte = Integer.parseInt(this.qteTextField.getText());
						if ( qte <0 )
						{
							correct = false;
							qteErrorLabel.setVisible(true);
						}
		} catch (NumberFormatException e) {
			correct = false;
			qteErrorLabel.setVisible(true);
		}

				//if data is correct, send data to socket command
		if (correct == true) {
			// The input is correct, so that means we can hide all the errors labels :
			rebusErrorLabel.setVisible(false);
			rebusErrorLabelLessOrEqualTo.setVisible(false);
			boxErrorLabel.setVisible(false);
			palErrorLabel.setVisible(false);
			qteErrorLabel.setVisible(false);

			// The input is correct so thoses lines should not throw any exception
			rebus = Integer.parseInt(rebusTextField.getText());
			box = Integer.parseInt(boxTextField.getText());
			pal = Integer.parseInt(this.palTextField.getText());
			lot = (String) lotComboBox.getSelectedItem();
			qte = Integer.parseInt(this.qteTextField.getText());

			// Open the window on production progress monitoring
			this.managementFrame.setParameters(lot, qte, pal);
			this.setVisible(false);
			this.managementFrame.setVisible(true);
			
			
			// Send the parameters to the server :
			// /!\ IMPORTANT NOTE /!\ Here we send the parameters AFTER having displayed the ManagementFrame, 
			// that way, it will receive potential errors after being visible and will thus hide properly
			threadCmd.sendParameters(lot, rebus, box, pal, qte);
		}

	}//GEN-LAST:event_ValidateButtonActionPerformed

	private void lotComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_lotComboBoxActionPerformed
		// nothing to do
	}//GEN-LAST:event_lotComboBoxActionPerformed

	private void qteTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_qteTextFieldActionPerformed
		// nothing to do
	}//GEN-LAST:event_qteTextFieldActionPerformed
	// Variables declaration - do not modify//GEN-BEGIN:variables
	private javax.swing.JButton ValidateButton;
	private javax.swing.JLabel boxErrorLabel;
	private javax.swing.JLabel boxLabel;
	private javax.swing.JTextField boxTextField;
	private javax.swing.JComboBox lotComboBox;
	private javax.swing.JLabel palErrorLabel;
	private javax.swing.JLabel palLabel;
	private javax.swing.JTextField palTextField;
	private javax.swing.JPanel panelA;
	private javax.swing.JLabel parametersLabel;
	private javax.swing.JLabel qteErrorLabel;
	private javax.swing.JLabel qteLabel;
	private javax.swing.JTextField qteTextField;
	private javax.swing.JLabel rebusErrorLabel;
	private javax.swing.JLabel rebusErrorLabelLessOrEqualTo;
	private javax.swing.JLabel rebusLabel;
	private javax.swing.JTextField rebusTextField;
	// End of variables declaration//GEN-END:variables
}
